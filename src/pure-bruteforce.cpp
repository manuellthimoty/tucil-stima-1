#include <bits/stdc++.h>
using namespace std;

char input[100][100];
bool used[100][100];

int n;
bool solusi = false;
int it = 0;
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


        used[x][i] = true;

        if (cek(x, i)){ 
            solve(x + 1);
        }

        used[x][i] = false;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

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

    if (!solusi)
        cout << "Tidak ada solusi\n";
    // cout << it << endl;
    return 0;
}
