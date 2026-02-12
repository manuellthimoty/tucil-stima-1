#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// hal hal yg dibutuhkan untuk permuttasi
vector<int> arr;
vector<bool> used;
vector<vector<int>> permutations;
int n;

// set banyak daerah yg mungkin

vector<vector<string>> ans;
vector<string> input;
void generatePermutations(vector<int> curr ={}){
    if(n == curr.size()){
        for(int i = 0 ; i < curr.size()-1 ; i++){
            if(abs(curr[i] - curr[i+1]) == 1){
                return;
            }
        }
        permutations.push_back(curr);
        return;
    }
    for(int i = 0 ; i < arr.size() ; i++){
        if(!used[i]){
            used[i] = true;
            curr.push_back(arr[i]);
            generatePermutations(curr);
            curr.pop_back();
            used[i] = false ;
        }
    }
}

void generateAnswer(vector<string> in, vector<int> pos){
    vector<string> copyin;
    for(auto s : in) copyin.push_back(s);
    int posSize = pos.size();
    for(int i = 0 ; i < posSize ; i++){
        copyin[pos[i] -1][i] = '#';
    }
    ans.push_back(copyin);
}


void solve(){
    
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    n = 9;
    for(int i = 1 ; i <= n ; i++){
        arr.push_back(i);
        used.push_back(false);
    }
    generatePermutations();
    vector<vector<char>> regions(n+1, vector<char>(n+1));
    for(int i = 1 ; i <= n ; i++){
        string line ; cin >> line;
        input.push_back(line);
        for(int j = 1 ; j<= n ; j ++){
            regions[i][j] = line[j-1];
        }
    }
    // for(int i = 1; i <= n; i++){
    //     for(int j = 1; j <= n; j++){
    //         cout << regions[i][j];
    //     }
    //     cout << endl;
    // }
    cout << permutations.size() << endl;
    for(auto p : permutations){
        // val dari p adalah nilai2 kolomnya.
        bool valid = true;
        // map<int,int> countSum;
        // for(int i = 1; i <= n ; i++){
        //     int curVal = i + p[i-1];
        //     countSum[curVal] ++ ;
        //     if(countSum[curVal] > 1){
        //         cout << curVal;
        //         valid = false;
        //         break;
        //     }
        // }
        // map<int,int> countDiff;
        // for(int i = 1; i <= n; i++){
        //     int curDiff = p[i-1]- i;
        //     countDiff[curDiff]++;
        //     if(countDiff[curDiff] > 1){
        //         valid = false;
        //         break;
        //     }
        // }
        // map<char,int> countRegion;
        int countRegion[256] = {0};
        for(int i = 1;  i <= n ; i++){
            int curReg = regions[p[i-1]][i];
            countRegion[curReg] ++;
            if(countRegion[curReg] > 1){
                valid = false;
                break;
            }
        }
        if(valid){
            generateAnswer(input,p);
        }
    }
    for(auto a : ans){
        for(auto line : a){
            cout << line << endl;
        }
        cout << endl;
    }
    
    return 0;
}
