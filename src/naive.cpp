#include <bits/stdc++.h>
using namespace std;

char input[100][100];
bool used[100][100];

int n;
bool solusi = false;
int it = 0;
int countsleep = 0;
int sleepduration = 100;
bool cek(int x, int y){
    char warna = input[x][y];

    for (int i = 0; i < x; i++){
        for (int j = 0; j < n; j++){
            if (used[i][j]){
                if (warna == input[i][j]) return false;

                if (j == y) return false;
                if(x == i) return false;
                if (abs(x - i) == 1 && abs(y - j) == 1)
                    return false;
            }
        }
    }
    return true;
}

void solve(int x = 0){
    it ++;
    if(solusi) return;
    if(it % 50 == 0){
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                if(used[i][j]) cout << "#";
                else cout << input[i][j];
            }
            cout << endl;
        }
        cout << endl;
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(sleepduration));
        countsleep++;
    }
    if (x == n){
        // solusi = true;
        bool found = true;
        vector<pair<int,int>> queens;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if(used[i][j]){
                    queens.push_back(make_pair(i,j));
                }
            }
        }
        for(int i = 0 ; i < n ; i++){
            for(int j = i+1 ; j < n ; j++){
                int x1 = queens[i].first;
                int x2 = queens[j].first;
                int y1 = queens[i].second;
                int y2 = queens[j].second;
                if(x1 == x2 || y1 == y2) found = false;
                if(input[x1][y1] == input[x2][y2]) found = false;
                if(abs(x1-x2) == 1 && abs(y1-y2) == 1) found = false;
                if(!found) break;
            }
        }
        if(found){
            solusi = true;
            for(int i = 0 ; i < n ; i++){
                for(int j = 0 ; j < n ; j++){
                    if(used[i][j]){
                        cout << "#";
                    }
                    else{
                        cout << input[i][j];
                    }
                }
                cout << endl;
            }
            return;
        }
        return;
    }

    for (int i = 0; i < n; i++){
        if (solusi) return;


        used[x][i] = true;
        solve(x + 1);
        used[x][i] = false;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto start =  std::chrono::high_resolution_clock::now();
    cin >> n;

    for (int i = 0; i < n; i++){
        string s;
        cin >> s;
        for (int j = 0; j < n; j++){
            input[i][j] = s[j];
            used[i][j] = false;
        }
    }

    solve();
    cout << endl;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    cout << it << endl;
    cout.flush();

    auto ms_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << ms_duration.count() - countsleep * sleepduration << endl;
    cout.flush();

    if (!solusi)
        cout << 0 << endl;
    else{
        cout << 1 << endl;
    }
    cout.flush();
    return 0;
}
