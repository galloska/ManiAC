#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define pb push_back
#define fi first
#define se second

using namespace std;

const int inf = 1<<30;
const int MAXN = 5001;

int n;
int cont = 2;
int vis[MAXN];
int parent[MAXN];
int cap[MAXN][MAXN];
map<string,int> check;
vector<int> extra[MAXN];

int mapea(const string& cad) {
    if(check.find(cad) == check.end())
        check[cad] = cont++;
    return check[cad];
}

void add(int u,int v,int f) {
    cap[u][v] += f;
}

int bfs(int s,int t) {
    fill(vis, vis + n, 0);
    queue<int> q;
    vis[s] = 1;
    parent[s] = s;
    q.push(s);

    while(!q.empty()) {
        int u = q.front();
        q.pop();

        forn(v, n) {
            if(!vis[v] && cap[u][v] > 0) {
                vis[v] = 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    return vis[t];
}

int update(int s,int t,int f = inf) {
    int v = t;
    int flag = (f == inf);
    while(parent[v] != v) {
        int u = parent[v];
        if(flag) f = min(f, cap[u][v]);
        else {
            cap[u][v] -= f;
            cap[v][u] += f;
        }
        v = u;
    }
    return f;
}

int maxFlow(int s,int t) {
    int ans = 0;
    while(bfs(s, t)) {
        int f = update(s, t);
        update(s, t, f);
        ans += f;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int r,f,m,k;
    string cad;
    cin>>n>>r>>f>>m;

    set<string> A,B;
    int s = 0, t = 1;

    forn(i, r) {
        cin>>cad;
        add(s, mapea(cad), 1);
        A.insert(cad);
    }

    forn(i, f) {
        cin>>cad;
        add(mapea(cad), t, 1);
        B.insert(cad);
    }

    while(m--) {
        cin>>k;
        vector<int> uno, dos, tres;
        while(k--) {
            cin>>cad;
            if(A.find(cad) != A.end()) {
                int u = mapea(cad);
                uno.pb(u);
            } else if(B.find(cad) != B.end()) {
                int u = mapea(cad);
                dos.pb(u);
            } else {
                int u = mapea(cad);
                tres.pb(u);
            } 
        }

        int rutaI = cont++;
        int rutaO = cont++;
        add(rutaI, rutaO, 1);

        forn(i, uno.size())
            add(uno[i], rutaI, 1);

        forn(i, dos.size())
            add(rutaO, dos[i], 1);

        forn(i, tres.size()) {
            add(rutaO, tres[i], 1);
            add(tres[i], rutaI, 1);
        }
    }

    n = cont;
    cout<<maxFlow(s, t)<<endl;
    return 0;
}
