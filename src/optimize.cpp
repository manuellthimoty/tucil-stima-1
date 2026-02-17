#include <bits/stdc++.h>
using namespace std;

char input[100][100];
bool used[100][100];
bool colorUsed[256];
bool columnUsed[100];
int pos[100];
int n;
bool solusi = false;
int it = 0;
int countsleep = 0;
int sleepduration = 0;
int every = 0;

bool cek(int x, int y){
    if(columnUsed[y]) return false;
    if(colorUsed[input[x][y]]) return false;
    if(x > 0 && abs(pos[x-1] - y) == 1)
        return false;

    return true;
}

void solve(int x = 0){
    it ++;
    if(it % every == 0){
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
        solusi = true;

        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (used[i][j]) cout << "#";
                else cout << input[i][j];
            }
            cout << endl;
        }
        return;
    }

    for (int i = 0; i < n; i++){
        if (solusi) return;
        if (cek(x, i)){
            used[x][i] = true;
            pos[x] = i;
            columnUsed[i] = true;
            colorUsed[input[x][i]] = true;
            solve(x + 1);

            used[x][i] = false;
            columnUsed[i] = false;
            colorUsed[input[x][i]] = false;
        }
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
    cin >> every;

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