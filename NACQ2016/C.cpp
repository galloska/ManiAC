#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back

using namespace std;

const int MAXN = 101;

int n;
int ans;
int num[MAXN];
lli memo[MAXN][10001];
vector<pii> lista[MAXN];

int Dijsktra() {
    vector<int> dist(n, 1e8);
    priority_queue<pii, vector<pii>, greater<pii> > q;
    q.push(pii(0, 0));
    dist[0] = 0;
    
    while(!q.empty()) {
        int u = q.top().se;
        int d = q.top().fi;
        q.pop();

        if(d > dist[u]) continue;

        forn(i, lista[u].size()) {
            int v = lista[u][i].fi;
            d = lista[u][i].se;
            if(dist[u] + d < dist[v]) {
                dist[v] = dist[u] + d;
                q.push( pii(dist[v], v) );
            }
        }
    }

    return dist[n - 1];
}

lli DP(int u,int d) {
    if(memo[u][d] != -1LL<<60) return memo[u][d];
    if(u == n - 1) return memo[u][d] = (d == ans ? num[u] : -1LL<<30);
    lli res = -1LL<<30;
    forn(i, lista[u].size()) {
        int v = lista[u][i].fi;
        if(d + lista[u][i].se > ans) continue;
        res = max(res, DP(v, d + lista[u][i].se));
    }
    return memo[u][d] = res + num[u];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int m,a,b,c;
    cin>>n;
    forn(i, n) cin>>num[i];
    cin>>m;

    while(m--) {
        cin>>a>>b>>c;
        a--,b--;
        lista[a].pb(pii(b, c));
        lista[b].pb(pii(a, c));
    }
    ans = Dijsktra();
    if(ans == 1e8) {
        cout<<"impossible"<<endl;
        return 0;
    }

    forn(i, n)
    forn(j, ans + 1)
        memo[i][j] = -1LL<<60;

    cout<<ans<<" "<<DP(0, 0)<<endl;
    return 0;
}
