#include<bits/stdc++.h>
#define ll long long
using namespace std;
typedef pair<int,int> pi;
const ll mod1 = 1000000007,mod2 = 1000000009,mul = 32;

int overLap(string &see){
    int border = 0;
    vector<int> kmp(see.size(),0);
    for(int i = 1; i < see.size();++i){
        while(border > 0 && see[i] != see[border])
            border = kmp[border-1];
        if(see[i] == use[border])
            ++border;
        else border = 0;
        kmp[i] = border;
    }
    return kmp.back();
}


void createGraph(map<ll,vector<string>> &tr,vector<vector<pi>> &g,unordered_map<string,int> &ids){
    for(auto &ve:tr){
        for(int i = 0; i < ve.size();++i){
            for(int j = 0; j < ve.size();++j){
                if(i == j) continue;
                int id1, id2;
                if(!ids.count(ve[i]))
                    ids[ve[i]] = (int)ids.size();
                if(!ids.count(ve[j]))
                    ids[ve[j]] = (int)ids.size();
                id1 = ids[ve[i]], id2 = ids[ve[j]];
                string send = ve[i] + "$" + ve[j];
                int imp = overLap(send);
                g.push_back({id1,imp});
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    map<ll,vector<string>> tr;
    string line;
    ll dp1[102];
    ll dp2[102];
    dp1[0] = 1;
    dp2[0] = 1;
    for(int i = 1; i < 102;++i){
        dp1[i] = dp1[i-1]*mul;
        dp2[i] = dp2[i-1]*mul;
        dp1[i] %= mod1;
        dp2[i] %= mod2;
    }
    int words = 0;
    while(cin >> line){
        ll has1 = 0;
        ll has2 = 0;
        for(int i = 0; i < 12;++i){
            has1 *= mul;
            has2 *= mul;
            has1 += line[i];
            has2 += line[i];
            if(has1 >= mod1) has1 %= mod1;
            if(has2 >= mod2) has2 %= mod2;
        }
        tr[(has1<<32)+has2].push_back(line);
        for(int i = 0,int j = 12; j < line.size();++i,++j){
            has1 -= dp1[11]*line[i];
            has2 -= dp2[11]*line[i];
            if(abs(has1) >= mod1) has1 %= mod1;
            if(abs(has2) >= mod2) has2 %= mod2;
            if(has1 < 0) has1 += mod1;
            if(has2 < 0) has2 += mod2;
            has1 *= mul;
            has2 *= mul;
            if(has1 >= mod1) has1 %= mod1;
            if(has2 >= mod2) has2 %= mod2;
            has1 += line[j];
            has2 += line[j];
            if(has1 >= mod1) has1 -= mod1;
            if(has2 >= mod2) has2 -= mod2;
            tr[(has1<<32)+has2].push_back(line);
        }
        ++words;
    }
    unordered_map<string,int> ids;
    unordered_map<int,string> reverIds;
    vector<vector<pi>> g(words);
    createGraph(tr,g,ids);
    for(auto va:ids)
        reverIds[va.second] = va.first;
    string ans = reverIds[0];
    vector<int> seen(words,0);
    seen[0] = 1;
    int last = 0;
    while(1){
        int next = -1;
        int val = 0;
        for(auto va:g[last]){
            if(!seen[va.first] && va.second > val)
                next = va.first,val = va.second;
        }
        if(next == -1)break;
        ans += reverIds[next].substr(val,200);
        last = next;
    }
    cout << ans << "\n";
    return 0;
}
