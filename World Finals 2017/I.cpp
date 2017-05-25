#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define pii pair<int,int>
#define psi pair<int,pii>
#define fi first
#define se second
#define pb push_back

using namespace std;

const int MAXN = 256;

int vis[MAXN];
vector<int> lista[MAXN];

int dfs(int u,int p) {
    if(u == p) return 1;
    vis[u] = 1;
    int ans = 0;
    forn(i, lista[u].size()) {
        int v = lista[u][i];
        if(!vis[v]) ans = max(ans, dfs(v, p));
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    char a,b;
    cin>>n>>m;

    forn(i, n) {
        cin>>a>>b;
        lista[a].pb(b);
    }

    string uno,dos;
    forn(i, m) {
        cin>>uno>>dos;

        if(uno.size() != dos.size()) {
            cout<<"no"<<endl;
            continue;
        }

        int f = 1;
        forn(i, uno.size()) {
            fill(vis, vis + MAXN, 0);
            if(!dfs(uno[i], dos[i]))
                f = 0;
        }

        if(f) cout<<"yes"<<endl;
        else cout<<"no"<<endl;
    }
    return 0;
}
