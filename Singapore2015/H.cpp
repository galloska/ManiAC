#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=1;i<=n;i++)
#define lli long long int
#define fi first
#define se second
#define pii pair<int,int>
#define pb push_back

using namespace std;

const int MAXN = 3001;

lli sum[MAXN];
lli dp[MAXN][MAXN];
lli suffix[MAXN][MAXN];

int main() {
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        int n;
        cin>>n;
        forn(i, n) cin>>sum[i];
        forn(i, n) sum[i] += sum[i - 1];

        lli ans = 0;
        for(int i=n;i>=1;i--) {
                for(int j=n;j>=i;j--) {
                        int ini = j + 1, fin = n + 1;
                        while(ini < fin) {
                                int med = (ini + fin) / 2;
                                if(sum[med] - sum[j] < sum[j] - sum[i - 1]) ini = med + 1;
                                else fin = med;
                        }
                        dp[i][j] = suffix[j + 1][ini] + 1;
                        suffix[i][j] = max(dp[i][j], suffix[i][j + 1]);
                }
        }

        forn(i, n)
                ans = max(ans, dp[1][i]);

        cout<<ans<<endl;
        return 0;
}
