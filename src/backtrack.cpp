// #include <bits/stdc++.h>
// using namespace std;
// typedef long long ll;

// vector<int> arr;
// vector<bool> used;
// bool valid = false;
// int n;
// ll iterationCount = 0;

// vector<vector<string>> ans;
// vector<vector<string>> tempAns;
// vector<string> input;
// vector<vector<char>> regions;

// void generateCopy(vector<string> in, vector<int> pos){
//     vector<string> copyin;
//     for(auto s : in) copyin.push_back(s);
//     int posSize = pos.size();
//     for(int i = 0 ; i < posSize ; i++){
//         copyin[pos[i]][i] = '#';
//     }
//     tempAns.push_back(copyin);
// }


// void generateAnswer(vector<string> in, vector<int> pos){
//     vector<string> copyin;
//     for(auto s : in) copyin.push_back(s);
//     int posSize = pos.size();
//     for(int i = 0 ; i < posSize ; i++){
//         copyin[pos[i]][i] = '#';
//     }
//     ans.push_back(copyin);
//     tempAns.push_back(copyin);
// }

// bool check(vector<int> curr){
//     int countRegion[256] = {0};
//     for(int i = 0 ; i < curr.size() ; i++){
//         int curReg = regions[curr[i]][i];
//         countRegion[curReg] ++;
//         if(countRegion[curReg] > 1){
//             return false;
//         }
//         if(i < n-1 && abs(curr[i] - curr[i+1]) <=1) return false;
//     }
//     return true;
// }
// void outputProgress() {
    
//     if(tempAns.size() > 0) {
//         for(auto a : tempAns){
//             for(auto line : a){
//                 cout << line << endl;
//             }
//             cout << endl;
//         }
//         cout.flush();
//         tempAns.clear();
//     }
// }

// void generateProgress(vector<int> currProgress) {
//     vector<string> progressCopy;
//     for(auto s : input) progressCopy.push_back(s);
//     int posSize = currProgress.size();
//     for(int i = 0 ; i < posSize ; i++){
//         progressCopy[currProgress[i]][i] = '#';
//     }
//     tempAns.push_back(progressCopy);
// }

// void solve(vector<int> curr = {}){
//     // Output intermediate results every 1000 iterations
//     // if(valid) return;
//     if(n == (int)curr.size()){
//         iterationCount++;

//         if(iterationCount % 100 == 0) {
//             generateProgress(curr);
//             outputProgress();
//         }
//         if(check(curr)){
//             generateAnswer(input,curr);
//             // valid = true;
//         }
//         return;
//     }
//     for(int i = 0 ; i < (int) arr.size() ; i++){
//         if(!used[i]){
//             used[i] = true;
//             curr.push_back(arr[i]);
//             solve(curr);
//             curr.pop_back();
//             used[i] = false;
//         }
//     }
// }

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     cin >> n;
//     for(int i = 0; i < n ; i++){
//         arr.push_back(i);
//         used.push_back(false);
//     }
//     regions.resize(n, vector<char>(n));

//     for(int i = 0 ; i < n ; i++){
//         string line ; cin >> line;
//         input.push_back(line);
//         for(int j = 0 ; j< n ; j ++){
//             regions[i][j] = line[j];
//         }
//     }

//     solve();
    
//     // Output remaining results at the end
//     for(auto a : ans){
//         for(auto line : a){
//             cout << line << endl;
//         }
//         cout << endl;
//     }
    
//     return 0;
// }
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> arr;
vector<bool> used;
bool found = false;
int n;
ll iterationCount = 0;

vector<vector<string>> ans;  
vector<vector<string>> tempAns;  
vector<string> input;
vector<vector<char>> regions;


void generateAnswer(vector<string> in, vector<int> pos){
    vector<string> copyin;
    for(auto s : in) copyin.push_back(s);
    int posSize = pos.size();
    for(int i = 0 ; i < posSize ; i++){
        copyin[pos[i]][i] = '#';
    }
    ans.push_back(copyin);  
    tempAns.push_back(copyin);
}

void generateProgress(vector<int> currProgress) {
    vector<string> progressCopy;
    for(auto s : input) progressCopy.push_back(s);
    int posSize = currProgress.size();
    for(int i = 0 ; i < posSize ; i++){
        progressCopy[currProgress[i]][i] = '#';
    }
    tempAns.push_back(progressCopy);
}

bool check(vector<int> curr){
    int countRegion[256] = {0};
    for(int i = 0 ; i < curr.size() ; i++){
        int curReg = regions[curr[i]][i];
        countRegion[curReg] ++;
        if(countRegion[curReg] > 1){
            return false;
        }
    }
    return true;
}

void outputProgress() {
    if(tempAns.size() > 0) {
        for(auto a : tempAns){
            for(auto line : a){
                cout << line << endl;
            }
            cout << endl;
        }
        cout.flush();
        tempAns.clear();
    }
}

void solve(vector<int> curr = {}){
    if(found) return;
    if(n == (int)curr.size()){
        iterationCount++;

        if(check(curr)){
            generateAnswer(input, curr);
            found = true;
        }
        
       
        if(iterationCount % 2000 == 0) {
            if(tempAns.size() == 0) {
                // Jika tidak ada solusi di 1000 iterasi ini, show progress
                generateProgress(curr);
            }
            outputProgress();
        }
        
        return;
    }
    
    for(int i = 0 ; i < (int) arr.size() ; i++){
        if(found) return;
        if(!used[i]){
            if(!curr.empty() && abs(curr.back() - arr[i]) == 1) continue;
            used[i] = true;
            curr.push_back(arr[i]);
            solve(curr);
            curr.pop_back();
            used[i] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i = 0; i < n ; i++){
        arr.push_back(i);
        used.push_back(false);
    }
    regions.resize(n, vector<char>(n));

    for(int i = 0 ; i < n ; i++){
        string line ; cin >> line;
        input.push_back(line);
        for(int j = 0 ; j< n ; j ++){
            regions[i][j] = line[j];
        }
    }

    solve();
    
   
    outputProgress();
    
    // Output final solutions yang belum dikirim
    for(auto a : ans){
        for(auto line : a){
            cout << line << endl;
        }
        cout << endl;
    }
    
    return 0;
}