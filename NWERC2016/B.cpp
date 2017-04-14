#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define fi first
#define se second
#define pii pair<int,int>
#define pb(a) push_back(a)

using namespace std;

const int INF = 1<<30;
const int MAXN = 100001;

int cont;
int nueva;
int aux[5];
int padre[MAXN];
int dp[MAXN][5];
list<int> lista[MAXN];
list<int> CFCs[MAXN];
int numeracion, top_activo;
int low[MAXN], num[MAXN], activo[MAXN];

void ObtenerCFCs_(int u) {
    activo[top_activo++] = u;
    low[u] = num[u] = ++numeracion;
    for(auto it: lista[u]) {
        int v = it;
        if (!num[v]) ObtenerCFCs_(v);
        low[u] = min(low[u], low[v]);
    }
    if (low[u] == num[u]) {
        while (activo[top_activo - 1] != u) {
            CFCs[nueva].pb(activo[--top_activo]);
            low[activo[top_activo]] = INF;
        }
        CFCs[nueva++].pb(activo[--top_activo]);
        low[u] = INF;
    }
}

void ObtenerCFCs(int n) {
    numeracion = nueva = 0;
    fill(num, num + n, 0);
    fill(low, low + n, 0);
    forn(i, n)
        if (!num[i]) ObtenerCFCs_(i);

    forn(i, nueva) {
        int j = 0;
        for(auto u: CFCs[i]) {
            padre[u] = i;
            low[u] = j++;
        }
    }
}

void dfs(int u) {
    activo[u] = 1;
    for(auto v: CFCs[u]) 
        for(auto p: lista[v]) 
            if(padre[p] != u && !activo[ padre[p] ]) dfs(padre[p]);
    num[cont++]= u;
}

int fin, region;

int DP(int ini) {
    int tam = 0;
    for(auto it: CFCs[region])
        if(it != ini)
            aux[tam++] = it;
    sort(aux, aux + tam);
    int maxi = 0;
    do{
        int act = ini;
        int len = 0;
        while(act != fin) {
            if(find(lista[act].begin(), lista[act].end(), aux[len]) 
                != lista[act].end()) act = aux[len++];
            else break;
        }
        if(act == fin) maxi = max(maxi, len);
    }while(next_permutation(aux, aux + tam));
    return maxi;
}

int longestPath(int u, int h) {
    int maxi = 0;
    region = h;
    for(auto v: CFCs[h]) {
        fin = v;
        int val = DP(u);
        maxi = max(maxi, val);
        for(auto p: lista[v]) {
            if(padre[p] == h) continue;
            maxi = max(maxi, val + dp[padre[p]][low[p]] + 1);
        }
    }
    return maxi;
}

int main() {
    ios_base::sync_with_stdio();
    cin.tie(0);
    int n,m,a,b,u,v;
    cin>>n>>m;

    forn(i, m) {
        cin>>a>>b;
        a--,b--;
        lista[a].pb(b);
    }

    ObtenerCFCs(n);
    
    fill(activo, activo + nueva, 0);
    forn(i, nueva)
        if(!activo[i])
            dfs(i);

    int maxi = 0;
    forn(i, cont) {
        u = num[i];
        int j = 0;
        for(auto v: CFCs[u]) {
            dp[u][j] = longestPath(v, u);
            maxi = max(maxi, dp[u][j++]);
        }
    }
    cout<<maxi + 1<<endl;
    return 0;
}
