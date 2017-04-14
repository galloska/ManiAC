#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define fi first
#define se second
#define pii pair<int,int>
#define pb(a) push_back(a)

using namespace std;

const int MAXN = 1000005;

int dist[3][MAXN];
vector<pii> lista[2][MAXN];

void bfs(int s,int n,int p) {
    fill(dist[p], dist[p] + n, 1e8);
    dist[p][s] = 0;
    deque<int> q;
    q.push_back(s);

    while(!q.empty()) {
        int u = q.front();
        q.pop_front();

        forn(i, lista[(p != 0)][u].size()) {
            int v = lista[(p != 0)][u][i].fi;
            int d = lista[(p != 0)][u][i].se;
            if(dist[p][u] + d < dist[p][v]) {
                dist[p][v] = dist[p][u] + d;
                if(d) q.push_back(v);
                else q.push_front(v);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio();
    cin.tie(0);
    int n,a,b,c;
    cin>>n>>a>>b;
    while(a--) {
        cin>>c;
        c--;
        lista[1][n].pb(pii(c, 0));
    }

    while(b--) {
        cin>>c;
        c--;
        lista[1][n + 1].pb(pii(c, 0));
    }

    forn(i, n) {
        cin>>a;
        while(a--) {
            cin>>c;
            c--;
            lista[0][i].pb(pii(c, 1));
            lista[1][c].pb(pii(i, 1));
        }
    }

    bfs(0, n + 2, 0);
    bfs(n, n + 2, 1);
    bfs(n + 1, n + 2, 2);

    int mini = 1e8;
    forn(i, n) {
        mini = min(mini, dist[0][i] + dist[1][i] + dist[2][i]);
    }

    if(mini < 1e8) cout<<mini<<endl;
    else cout<<"impossible"<<endl;
    return 0;
}
