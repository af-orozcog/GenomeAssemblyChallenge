#include<bits/stdc++.h>
using namespace std;
typedef pair<int,string> pi;
vector<string> ans;
vector<vector<pi>> g;

vector<pi> seen;
void dfs(int p,string &add){
    seen.push_back({p,add});
    if(g[p].size() == 0){
        while(seen.size()){
            if((int)g[seen.back().first].size() != 0)break;
            ans.push_back(seen.back().second);
            seen.pop_back();
        }
        if(seen.size()){
            int next = seen.back().first;
            string ad = seen.back().second;
            seen.pop_back();
            dfs(next,ad);
        }
        return;
    }
    int next = g[p].back().first;
    string ad = g[p].back().second;
    g[p].pop_back();
    dfs(next,ad);
    return;
}

string important[5396];
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    unordered_map<string,int> dif;
    for(int i = 0; i < 5396;++i){
        cin >> important[i];
        int val = dif.size();
        if(!dif.count(important[i].substr(0,(int)important[i].size()-1)))
            dif[important[i].substr(0,(int)important[i].size()-1)] = val;
        val = dif.size();
        if(!dif.count(important[i].substr(1,(int)important[i].size())))
            dif[important[i].substr(1,(int)important[i].size())] = val;
    }
    int n = dif.size();
    g.resize(n);
    for(int i = 0; i < 5396;++i){
        int from = dif[important[i].substr(0,(int)important[i].size()-1)];
        int to = dif[important[i].substr(1,(int)important[i].size())];
        string wut = ""; wut += important[i].back();
        g[from].push_back({to,wut});
    }
    string ad = "";
    dfs(0,ad);
    reverse(ans.begin(),ans.end());
    for(int i = 0; i < (int)ans.size();++i)
        cout << ans[i];
    cout << "\n";
    return 0;
}
