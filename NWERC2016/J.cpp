#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define fi first
#define se second
#define pii pair<int,int>
#define pb(a) push_back(a)

using namespace std;

const int MAXN = 1000001;

typedef long long Dato;
typedef vector<Dato> Vec;
typedef vector<Vec> Mat;
typedef vector<int> Lista;
const Dato INF = 1LL<<50;

struct Flujo {
    int n;
    Lista padre;
    Mat cap, flujo;
    vector<Dato> dist;
    vector<Lista> aristas;

    Flujo(int N) : dist(N), padre(N), aristas(N),
        cap(N, Vec(N)), flujo(N, Vec(N)), n(N) {}

    void AgregarArista(int u, int v, Dato c) {
        flujo[v][u] += c; // Solo dirigidas!
        cap[u][v] += c, cap[v][u] += c;
        aristas[u].push_back(v);
        aristas[v].push_back(u);
    }

    // Flujo maximo mediante Edmonds-Karp O(VE^2).
    Dato ActualizarFlujo(int u, Dato f) {
        int p = padre[u];
        if (p == u) return f;
        f = ActualizarFlujo(p, min(
            f, cap[p][u] - flujo[p][u]));
        flujo[p][u] += f;
        flujo[u][p] -= f;
        return f;
    }

    Dato AumentarFlujo(int s, int t) {
        fill(padre.begin(), padre.end(), -1);
        queue<int> q; q.push(s); padre[s] = s;
        while (!q.empty()) {
            int u = q.front();
            q.pop(); if (u == t) break;
            for (int i = 0; i < aristas[u].size(); ++i) {
                int v = aristas[u][i];
                if (flujo[u][v] == cap[u][v] ||
                    padre[v] != -1) continue;
                padre[v] = u, q.push(v);
            }
        }
        if (padre[t] == -1) return 0;
        return ActualizarFlujo(t, INF);
    }

    Dato EdmondsKarp(int s, int t) {
        Dato flujo_maximo = 0, f;
        while (f = AumentarFlujo(s, t))
            flujo_maximo += f;
        return flujo_maximo;
    }

    // Flujo maximo mediante Dinic O(V^2E).
    Dato FlujoBloqueante(int u, int t, Dato f) {
        if (u == t) return f; Dato fluido = 0;
        for (int i = 0; i < aristas[u].size(); ++i) {
            if (fluido == f) break; int v = aristas[u][i];
            if (dist[u] + 1 > dist[v]) continue;
            Dato fv = FlujoBloqueante(v, t,
                min(f - fluido, cap[u][v] - flujo[u][v]));
            flujo[u][v] += fv, fluido += fv;
            flujo[v][u] -= fv;
        }
        return fluido;
    }

    Dato Dinic(int s, int t) {
        Dato flujo_maximo = dist[t] = 0;
        while (dist[t] < INF) {
            fill(dist.begin(), dist.end(), INF);
            queue<int> q; q.push(s); dist[s] = 0;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int i = 0; i < aristas[u].size(); ++i) {
                    int v = aristas[u][i];
                    if (flujo[u][v] == cap[u][v] ||
                        dist[v] <= dist[u] + 1) continue;
                    dist[v] = dist[u] + 1, q.push(v);
                }
            }
            if (dist[t] < INF) flujo_maximo +=
                FlujoBloqueante(s, t, INF);
        }
        return flujo_maximo;
    }
};

int cola[MAXN];
int edge[MAXN];
vector<int> peso[MAXN];

int main() {
    ios_base::sync_with_stdio();
    cin.tie(0);
    int n,q,s;
    lli a,d;
    cin>>n>>q>>s;
    forn(i, s) {
        cin>>edge[i];
        edge[i]--;
    }
    forn(i, q) cin>>cola[i];
    
    lli total = 0, sum = 0;
    
    vector<int> cap; 
    forn(i, n) {
        cin>>d;
        cap.pb(d);

        forn(j, s) {
            cin>>a;
            sum += a;
            peso[j].pb(a);
        }
    }

    int ini = 2 * n * q + n + 1;
    int fin = ini - 1;
    Flujo graph(2 * n * q + n + 2);
    forn(i, n)
        forn(j, s) 
            graph.AgregarArista(ini, i * q + edge[j], peso[j][i]);

    int aum = q * n;
    forn(i, n) {
        forn(j, q) {
            graph.AgregarArista(i * q + j, i * q + j + aum, cola[j]);
            if(i < n - 1)
                graph.AgregarArista(i * q + j + aum, (i + 1) * q + j , INF);
            graph.AgregarArista(i * q + j + aum, 2 * aum + i , INF);
        }
        graph.AgregarArista(2 * aum + i, fin , cap[i]);
    }

    lli flow = graph.EdmondsKarp(ini, fin);
    if(flow < sum) cout<<"impossible"<<endl;
    else cout<<"possible"<<endl;
    return 0;
}
