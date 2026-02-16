#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<string> input;
int n ;
vector<string> ans;
bool valid = false;
vector<vector<bool>> used;

bool isvalid(int x,int y){
    char currcol = input[x][y];
    for(int i = 0 ; i < x ; i++){
        for(int j = 0 ; j < n ; j++){
            if(used[i][j]){
                if(currcol == input[i][j]) return false;
                if(j == y) return false;
                if(i == x) return false;
                if(abs(x-i) == 1 && abs(y-j) ==1 ) return false;
            }
        }
    }
    return true;
}

bool ceksemua(){
    vector<pair<int,int>> queens;
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            if(used[i][j]){
                queens.push_back(make_pair(i,j));
            }
        }
    }

    for(int i = 0 ; i < queens.size() ; i++){
        for(int j = i+1 ; j < queens.size() ; j++){
            int x1 = queens[i].first;
            int y1 = queens[i].second;
            int x2 = queens[j].first;
            int y2 = queens[j].second;
            if(input[x1][y1] == input[x2][y2]) return false;
            if(x1 == x2) return false;
            if(y1 == y2) return false;
            if(abs(x1-x2) == 1&& abs(y1-y2) == 1) return false;
        }
    }
    return true;
}

void solve(int x = 0){
    if (x == n){
        if(ceksemua()){
            valid = true;
            ans = input;
            for(int i = 0 ; i < n ; i++){
                for(int j = 0 ; j < n ; j++){
                    if(used[i][j]) ans[i][j] = '#';
                }
            }
        }
        return;
    }
    for(int i = 0 ; i < n ; i++){
        // if(isvalid(x,i)){
        //     used[x][i] = true;
        //     solve(x+1);
        //     if(valid) return;
        //     used[x][i] = false;
        // }
        used[x][i] = true;
        solve(x+1);
        if(valid) return;
        used[x][i] = false;
    }
}



int main() {
    cin >> n;
    for(int i = 0 ; i < n ; i++){
        string line ; cin >> line;
        input.push_back(line);
        ans.push_back(line);
    }

    used.resize(n, vector<bool>(n, false));
    solve();
    for(auto line : ans) cout << line << endl;

}