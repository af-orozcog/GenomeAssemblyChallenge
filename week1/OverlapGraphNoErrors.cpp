#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
const int MAXN = 1e6+5;
int a[MAXN],t[4*MAXN];
void build(int v, int tl, int tr){
    if(tl==tr)
        t[v]=a[tl];
    else{
        int tm = (tl+tr)/2;
        build(v*2,tl,tm);
        build(v*2+1,tm+1,tr);
        //depende la operación a realizar.
        t[v]= min(t[v*2],t[v*2+1]);
    }
}
int get(int v, int tl, int tr, int l, int r){
    if(l>r)
        //retornar valor neutro de la opéración.
        return 1000000000ll;
    if(tl==l&&tr==r)
        return t[v];
    int tm = (tl+tr)/2;
    return min(get(v*2,tl,tm,l,min(r,tm)),get(v*2+1,tm+1,tr,max(tm+1,l),r));

}


vector<int> sort_cyclic_shifts(string const& s) {
    int n = s.size();
    const int alphabet = 256;
    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++)
        cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++)
        cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}

vector<int> suffix_array_construction(string &s) {
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}

vector<int> lcp_construction(string const& s, vector<int> const& p) {
    int n = s.size();
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++)
        rank[p[i]] = i;

    int k = 0;
    vector<int> lcp(n-1, 0);
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = p[rank[i] + 1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k])
            k++;
        lcp[rank[i]] = k;
        if (k)
            k--;
    }
    return lcp;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string line;
    unordered_map<int,string> reverIds;
    unordered_set<string> uni;
    string glob = "";
    vector<int> acum;
    while(getline(cin,line)){
        if(line.size() == 0)break;
        int to = acum.size();
        reverIds[to] = line;
        if(uni.count(line)) continue;
        uni.insert(line);
        line += '$';
        glob += line;
        if(acum.size())
            acum.push_back(acum.back()+(int)line.size());
        else
            acum.push_back((int)line.size()-1);
    }
    vector<int> SA = suffix_array_construction(glob);
    vector<int> lcp = lcp_construction(glob,SA);
    vector<int> SAreverse(glob.size());
    for(int i = 0; i < SA.size();++i)
        SAreverse[SA[i]] = i;
    for(int i = 0; i < lcp.size();++i)
        a[i] = lcp[i];
    build(1,0,(int)lcp.size()-1);
    vector<vector<int>> closer(acum.size());
    for(int i = 0; i < SA.size();++i){
        int ind = lower_bound(acum.begin(),acum.end(),SA[i])-acum.begin();
        closer[ind].push_back(i);
    }
    vector<vector<pi>> g(acum.size());
    for(int i = 0; i < acum.size();++i){
        for(int j = 0; j < acum.size();++j){
            if(i == j) continue;
            int before = SAreverse[0];
            if(i != 0)
                before = SAreverse[acum[i-1]+1];
            int ind = lower_bound(closer[j].begin(),closer[j].end(),before)-closer[j].begin();
            if(ind != 0) --ind;
            else{
                g[j].push_back({i,0});
                continue;
            }
            int weigh = get(1,0,(int)lcp.size()-1,closer[j][ind],before-1);
            int check = acum[j]-SA[closer[j][ind]];
            if(check != weigh) weigh = 0;
            g[j].push_back({i,weigh});
        }
    }
    vector<int> seen(acum.size(),0);
    string ans = reverIds[0];
    int last = 0;
    seen[0] = 1;
    while(1){
        int next = -1;
        int ma = -1;
        for(int i = 0; i < g[last].size();++i)
            if(g[last][i].second > ma && !seen[g[last][i].first])
                ma = g[last][i].second, next = g[last][i].first;
        if(next == -1) break;
        ans += reverIds[next].substr(ma,200);
        seen[next] = 1;
        last = next;
    }
    int overlap = g[last][0].second;
    cout << ans.substr(overlap,ans.size()) << "\n";
    return 0;
}
