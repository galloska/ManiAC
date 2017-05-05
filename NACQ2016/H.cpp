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

int A[MAXN];
int B[MAXN];
int dp[MAXN][100001];
int dp2[MAXN][100001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin>>n;
    forn(i, n) cin>>A[i];
    cin>>m;
    forn(i, m) cin>>B[i];

    for(int i=n;i>=0;i--) {
        for(int sum=100000;sum>=0;sum--) {
            if(i == n) {
                if(sum == 0) dp[i][sum] = 0;
                else dp[i][sum] = 1e8;
                continue;
            }
            dp[i][sum] = dp[i + 1][sum];
            if(A[i] <= sum) dp[i][sum] = min(dp[i][sum], dp[i + 1][sum - A[i]] + 1);
        }
    }

    for(int i=m;i>=0;i--) {
        for(int sum=100000;sum>=0;sum--) {
            if(i == m) {
                if(sum == 0) dp2[i][sum] = 0;
                else dp2[i][sum] = 1e8;
                continue;
            }
            dp2[i][sum] = dp2[i + 1][sum];
            if(B[i] <= sum) dp2[i][sum] = min(dp2[i][sum], dp2[i + 1][sum-B[i]] + 1);
        }
    }

    int ans = 1e8;
    forn(i, 100001)
        if(i)
            ans = min(ans, dp[0][i] + dp2[0][i]);
    if(ans < 1e8) cout<<ans<<endl;
    else cout<<"impossible"<<endl;
    return 0;
}
