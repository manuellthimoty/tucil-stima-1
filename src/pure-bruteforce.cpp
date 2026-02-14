#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
vector<string> input;

bool isvalid(vector<int> check){
    for(int k = 0 ; k < check.size() ; k++){
        int i = check[k]/n;
        int j = check[k] % n;

    }
}

void generator(int size, vector<int> curr){
    if(size = curr.size()){
        return;        
    }
    for(int i = 0 ; i < n*n ; i++){
        curr.push_back(i);
        generator(size + 1, curr);
        curr.pop_back();
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for(int i = 0 ; i < n ; i++){
        string s ; cin >> s;
        input.push_back(s);
    }


}
