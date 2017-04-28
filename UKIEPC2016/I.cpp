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

typedef long double Long;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    Long c;
    cin >> c;
    
    int n;
    cin >> n;
    Long ans = 0;
    forn(i, n) {
        Long a, b;
        cin >> a >> b;
        ans += a*b;
    }
    cout << fixed << setprecision(9);
    cout << c * ans << '\n';

    return 0;
}
