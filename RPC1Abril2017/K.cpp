#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define pii pair<int,int>
#define psi pair<int,pii>
#define pb(a) push_back(a)
#define fi first
#define se second
 
using namespace std;
 
const int LOGN = 18;
const int MAXN = 50001;
 
int L[MAXN];
int R[MAXN];
int loga[MAXN];
int dist[MAXN];
double uno[101];
int P[LOGN][MAXN];
double prob[LOGN][MAXN][101];
vector<psi> lista[MAXN];
 
void bfs(int n) {
    fill(dist, dist + n, 1e8);
    queue<int> q;
    q.push(0);
    dist[0] = P[0][0] = 0;
 
    while(!q.empty()) {
        int u = q.front();
        q.pop();
 
        forn(i, lista[u].size()) {
            int v = lista[u][i].fi;
            if(dist[u] + 1 < dist[v]) {
                dist[v] = dist[u] + 1;
                q.push(v);
                P[0][v] = u;
                L[v] = lista[u][i].se.fi;
                R[v] = lista[u][i].se.se;
            }
        }
    }
}
 
void Preprocess(int n) {
	for(int j=0;j<=loga[n];j++) {
		forn(i, n)
			forn(p, 101) {
				if(!j) {
					if(p < L[i] || p > R[i]) prob[j][i][p] = (p < L[i] ? 0.0 : 1.0);
					else prob[j][i][p] = (p - L[i] + 1) / ( R[i] - L[i] + 1.0 );
					continue;
				}
                P[j][i] = P[j - 1][ P[j - 1][i] ];
                prob[j][i][p] = prob[j - 1][i][p] * prob[j - 1][ P[j - 1][i] ][p];
            }
    }
}
 
double LCA(int u,int v,int n) {
    if(dist[v] < dist[u]) swap(u, v);
 
    fill(uno, uno + 101, 1.0);
    for(int i=loga[n];i>=0;i--)
        if(dist[v] - (1<<i) >= dist[u]) {
            forn(p, 101) uno[p] *= prob[i][v][p];
            v = P[i][v];
        }
 
    if(u != v) {
        for(int i=loga[n];i>=0;i--)
            if(P[i][u] != P[i][v]) {
                forn(p, 101) uno[p] *= prob[i][v][p] * prob[i][u][p];
                v = P[i][v];
                u = P[i][u];
            }
 
        forn(p, 101) uno[p] *= prob[0][v][p] * prob[0][u][p];
    }
 
    double ans = 100.0 * uno[100];
    forn(i, 100) ans -= uno[i];
 
    return ans;
}

int ReadInt() {
	int result = 0;
	char ch;
	ch = getchar();
	while (true) {
		if (ch == EOF) break;
		if (ch >= '0' && ch <= '9') break;
		ch = getchar();
	}
	if(ch == EOF) return result;
	if (ch != '-') result = ch - '0';
	while (true) {
		ch = getchar();
		if (ch < '0' || ch > '9' || ch == EOF) break;
		result = result * 10 + (ch - '0');
	}
	return result;
}
 
int main() {
	for(int i=2;i<MAXN;i++)
        loga[i] = loga[i >> 1] + 1;
    int n,a,b,l,r,q;
    while((n = ReadInt() )&& n) {
        forn(i, n) lista[i].clear();
        forn(i, n - 1) {
            a = ReadInt();
			b = ReadInt();
			l = ReadInt();
			r = ReadInt();
            a--,b--;
            lista[a].pb( psi(b, pii(l, r)) );
            lista[b].pb( psi(a, pii(l, r)) );
        }
 
        bfs(n);
        Preprocess(n);
 
        q = ReadInt();
        while(q--) {
			a = ReadInt();
			b = ReadInt();
			printf("%.9lf\n", LCA(a - 1, b - 1, n));
        }
    }
    return 0;
}
