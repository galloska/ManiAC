#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<lli,lli>
#define fi first
#define se second
#define psi pair<int,pii>
#define pb push_back
#define vi vector<int>
#define vii vector< vi >

using namespace std;

const lli inf = 1LL<<50;
const int MAXN = 257;

int n,k;
pii num[MAXN];
lli memo[MAXN][MAXN][MAXN];

lli DP(int id,int cont,int last = 256) {
    if(cont > k) return inf;
    if(id == 256) return cont == k ? 0 : inf;
    if(memo[id][cont][last] != -1) return memo[id][cont][last];

    lli ans = DP(id + 1, cont, last);
    if(last == 256) {
        lli sum = 0ll;
        forn(i, n) {
            lli dif = abs(id - num[i].fi);
            sum += num[i].se * dif * dif;
        }
        ans = min(ans, DP(id + 1, cont + 1, id) + sum);
    } else {
        lli sum = 0ll;
        forn(i, n) {
            lli dif = abs(last - num[i].fi);
            lli dif2 = abs(id - num[i].fi);
            if(dif <= dif2) continue;
            sum -= num[i].se * dif * dif;
            sum += num[i].se * dif2 * dif2;
        }
        ans = min(ans, DP(id + 1, cont + 1, id) + sum);
    }

    return memo[id][cont][last] = ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>k;
    forn(i, n)
        cin>>num[i].fi>>num[i].se;
    forn(i, MAXN)
    forn(j, MAXN)
    forn(h, MAXN)
        memo[i][j][h] = -1;
    cout<<DP(0, 0)<<endl;
    return 0;
}
