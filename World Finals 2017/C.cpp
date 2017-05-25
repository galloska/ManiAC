#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define fi first
#define se second
#define psi pair<int,pii>
#define pb push_back
#define vi vector<int>
#define vii vector< vi >

using namespace std;

const int MAXN = 201;

int M[MAXN];
lli row[MAXN];
int vis[MAXN];
vector<int> A,B;
lli column[MAXN];
lli mat[MAXN][MAXN];
vector<int> lista[MAXN];

void addEdge(int u,int v) {
    lista[u].pb(v);
    lista[v].pb(u);
}

int tryKuhn(int a) {
    if(vis[a]) return 0;
    vis[a] = 1;
    forn(i, lista[a].size()) {
        int b = lista[a][i];
        if(M[b] == -1 || tryKuhn( M[b] )) {
            M[b] = a;
            return 1;
        }
    }
    return 0;
}

void maxMatching() {
    forn(i, B.size()) M[ B[i] ] = -1;

    forn(i, A.size()) {
        forn(j, A.size()) vis[ A[j] ] = 0;
        tryKuhn(A[i]);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    forn(i, n)
    forn(j, m)
        cin>>mat[i][j];
    
    lli ans = 0ll, res = 0ll, sum = 0ll;
    forn(i, n) {
        lli maxi = 0;
        forn(j, m) {
            maxi = max(maxi, mat[i][j]);
            res += (mat[i][j] > 0);
            sum += mat[i][j];
        }
        row[i] = maxi;
        ans += maxi;
    }

    forn(j, m) {
        lli maxi = 0;
        forn(i, n)
            maxi = max(maxi, mat[i][j]);
        column[j] = maxi;
        ans += maxi;
    }

    forn(i, n) A.pb(i);
    forn(i, m) B.pb(i + n);

    forn(i, n)
    forn(j, m)
        if(mat[i][j] && row[i] == column[j])
            addEdge(i, j + n);

    maxMatching();
    
    forn(i, m)
        if(M[i + n] != -1) {
            ans -= column[i];
            column[i] = 0;
            row[ M[i + n] ] = 0;
            res--;
        }
    forn(i, n)
        if(row[i])
            res--;
    forn(i, m)
        if(column[i])
            res--;

    ans += res;
    cout<<sum - ans<<endl;
    return 0;
}
