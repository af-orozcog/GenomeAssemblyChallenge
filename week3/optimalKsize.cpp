#include<bits/stdc++.h>
#define SIZE 400
#define LENGTH 100
using namespace std;


vector<int> topo;
vector<int> color;

void topoSort(int x, vector<vector<int>> &g){
    color[x] = 1;
    for(auto va:g[x])
        if(!color[va])
            topoSort(va,g);
    topo.push_back(x);
}

void dfs(int x,vector<vector<int>> &g){
    color[x] = 1;
    for(auto va:g[x])
        if(!color[va])
            dfs(va,g);
}

string reads[SIZE];
bool validate(int k){
    unordered_set<string> uni;
    for(int i = 0; i < SIZE;++i){
        for(int j = 0; j <= LENGTH-k;++j){
            string temp = reads[i].substr(j,k);
            uni.insert(temp);
        }
    }
    topo.clear();
    unordered_map<string, int> ids;
    for(auto &va:uni){
        string temp = va.substr(0,k-1);
        int next = ids.size();
        if(!ids.count(temp))
            ids[temp] = next;
        next = ids.size();
        temp = va.substr(1,k-1);
        if(!ids.count(temp))
            ids[temp] = next;
    }
    vector<vector<int>> g(ids.size());
    vector<vector<int>> gR(ids.size());
    for(auto &va:uni){
        string temp1 = va.substr(0,k-1);
        string temp2 = va.substr(1,k-1);
        g[ids[temp1]].push_back(ids[temp2]);
        gR[ids[temp2]].push_back(ids[temp1]);
    }
    bool posi = 1;
    for(int i = 0; i < g.size() && posi;++i){
        if(g[i].size() != gR[i].size())
            posi = 0;
    }
    if(!posi) return 0;
    color.clear();
    color.resize(ids.size(),0);
    topoSort(0,gR);
    reverse(topo.begin(),topo.end());
    fill(color.begin(),color.end(),0);
    int SCC = 0;
    for(int i = 0; i < topo.size();++i){
        if(!color[i]){
            dfs(i,g);
            ++SCC;
        }
    }
    return SCC == 1;
}


int main(){
    for(int i = 0; i < SIZE;++i)
        cin >> reads[i];
    int lo = 2, hi = LENGTH, ans = -1;
    while(lo <= hi){
        int mid = (lo+hi)>>1;
        if(validate(mid))
            lo = mid + 1, ans = mid;
        else hi = mid - 1;
    }
    cout << ans << "\n";
    return 0;
}
