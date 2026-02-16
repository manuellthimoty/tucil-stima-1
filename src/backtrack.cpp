#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> arr;
vector<bool> used;
bool found = false;
int n;
ll iterationCount = 0;
int countsleep = 0;
int sleepduration = 100;
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
        this_thread::sleep_for(chrono::milliseconds(sleepduration));
        countsleep++;
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
        
       
        if(iterationCount % 1000 == 0) {
            if(tempAns.size() == 0) {
                
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
            if(found) return;
            curr.pop_back();
            used[i] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto start =  std::chrono::high_resolution_clock::now();
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
    
    for(auto a : ans){
        for(auto line : a){
            cout << line << endl;
        }
        cout << endl;
    }
    cout.flush();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    cout << iterationCount << endl;
    cout.flush();
    auto ms_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << ms_duration.count() - countsleep * sleepduration << endl;
    cout.flush();
    if(found){
        cout << 1 << endl;
    }
    else{
        cout << 0 << endl;
    }
    cout.flush();
    
    return 0;
}