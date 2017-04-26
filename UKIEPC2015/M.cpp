#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<lli, lli>
#define fi first
#define se second
#define pb push_back
#define psi pair<int,pii>

using namespace std;

const int MAXN = 1001;

lli X[MAXN];
set<pii> check;
lli tiempo[MAXN];

int main() {
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        int m,n;
        cin>>m>>n;
        forn(i, m) cin>>tiempo[i];
        forn(i, n) cin>>X[i];

        vector<lli> ans;
        forn(i, n - m + 1) {
                int f = 1;
                lli a = X[i + 1] - X[i];
                lli b = tiempo[1] - tiempo[0];
                lli gcd = __gcd(a, b);
                pii vel = pii( a / gcd, b / gcd );
                forn(j, m - 1) {
                        a = X[i + j + 1] - X[i + j];
                        b = tiempo[j + 1] - tiempo[j];
                        gcd = __gcd(a, b);
                        pii vel2 = pii( a / gcd, b / gcd );
                        if(vel2 != vel) f = 0;
                }
                if(f && check.find(vel) == check.end()) {
                        ans.pb( X[i + 1] - X[i] );
                        check.insert(vel);
                }
        }
        cout<<ans.size()<<endl;
        sort(ans.begin(), ans.end());
        forn(i, ans.size()) {
                if(i) cout<<" ";
                cout<<ans[i];
        }
        if(ans.size()) cout<<endl;
        return 0;
}
