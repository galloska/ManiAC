#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define psi pair<int,pii>
#define fi first
#define se second
#define pb push_back

using namespace std;

int main() {
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        cout<<fixed<<setprecision(9);
        int n;
        cin>>n;
        double ans = 0.6321205588;
        if(n >= 12) {
                cout<<ans<<endl;
                return 0;
        }
        double fact = 1.0, next = 2.0, sign = 1.0;
        ans = 0.0;

        forn(i, n) {
                ans += sign * 1.0 / fact;
                fact *= next;
                next += 1.0;
                sign *= -1.0;
        }
        cout<<ans<<endl;
        return 0;
}
