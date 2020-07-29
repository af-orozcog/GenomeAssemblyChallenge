#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
vector<int> ans;
vector<vector<int>> g;
vector<vector<int>> gR;
vector<int> topo;
vector<int> color;

void topoSort(int x){
    color[x] = 1;
    for(auto va:gR[x])
        if(!color[va])
            topoSort(va);
    topo.push_back(x);
}

void dfsN(int p){
    color[p] = 1;
    for(auto va:g[p])
        if(!color[va])
            dfsN(va);
}

vector<int> seen;
void dfs(int p){
    seen.push_back(p);
    if(g[p].size() == 0){
        while(seen.size()){
            if((int)g[seen.back()].size() != 0)break;
            ans.push_back(seen.back());
            seen.pop_back();
        }
        if(seen.size()){
            int next = seen.back();
            seen.pop_back();
            dfs(next);
        }
        return;
    }
    int next = g[p].back();
    g[p].pop_back();
    dfs(next);
    return;
}

int main(){
    int n,m;
    scanf(" %d %d",&n,&m);
    g.resize(n);
    gR.resize(n);
    color.resize(n,0);
    int bad = 0;
    vector<int> inD(n,0);
    for(int i = 0; i < m;++i){
        int from,to;
        scanf(" %d %d",&from,&to);
        --from,--to;
        g[from].push_back(to);
        gR[to].push_back(from);
        ++inD[to];
    }
    for(int i = 0; i < n && !bad;++i)
        if(inD[i] != (int)g[i].size())
            ++bad;
    topoSort(0);
    int SCC = 0;
    reverse(topo.begin(),topo.end());
    fill(color.begin(),color.end(),0);
    for(auto va:topo){
        if(!color[va]){
            ++SCC;
            dfsN(va);
        }
    }
    if(SCC > 1 || bad){puts("0");return 0;}
    dfs(0);
    puts("1");
    reverse(ans.begin(),ans.end());
    for(int i = 0; i < (int)ans.size()-1;++i)
        printf("%d ",ans[i]+1);
    puts("");
    return 0;
}
