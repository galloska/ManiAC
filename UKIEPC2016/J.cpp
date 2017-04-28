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

const int MAXN = 101;

int num[MAXN];
int other[MAXN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,a,m,k;
    cin>>n;
    forn(i, n) cin>>num[i];

    cin>>m;
    forn(i, m) {
        cin>>k;
        int mask = 0;
        while(k--) {
            cin>>a;
            a--;
            mask |= (1<<a);
        }
        other[i] = mask;
    }

    int ans = 0;
    for(int mask=0;mask<(1<<n);mask++) {
        if(!mask) continue;

        int aux = 0;
        forn(j, m)
            aux |= other[j];

        int f = 1;
        forn(j, m)
            if(!(mask & other[j])) {
                f = 0;
                break;
            }

        forn(j, n)
            if(mask & (1<<j) && !(aux & (1<<j))) f = 0;
        if(!f) continue;

        int res = 0;
        forn(j, n)
            if(!(mask & (1<<j)))
                res += num[j];
        ans = max(ans, res);
    }

    cout<<ans<<endl;
    return 0;
}
