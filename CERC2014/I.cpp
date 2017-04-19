#include <bits/stdc++.h>
#define lli long long int
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pb push_back
#define pii pair<lli,lli>
#define fi first
#define se second

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t,n;
	lli a;
	char b;
	cin>>t;
	while(t--) {
		cin>>n;

		vector<pii> num;
		lli uno = 0, dos = 0;
		forn(i, n) {
			cin>>a>>b;
			num.pb(pii(a, b));
			if(b == 'B') {
				uno += a;
			}
			else {
				dos += a;
			}
		}

		if(!uno || !dos) {
			cout<<max(uno, dos)<<endl;
			continue;
		}

		lli gcd = __gcd(uno, dos);
		pii ratio = pii( uno / gcd, dos / gcd );

		uno = 0, dos = 0;
		int ans = 0;
		forn(i, n) {
			if(num[i].se == 'B') {
				lli act = uno;
				uno += num[i].fi;
				if(!dos || (dos * ratio.fi) % ratio.se != 0) continue;
				lli needed = (dos * ratio.fi) / ratio.se;
				if(act <= needed && uno >= needed && dos*ratio.fi >= ratio.fi) {
					uno = uno - needed;
					dos = 0;
					ans++;
				}
			}
			else {
				lli act = dos;
				dos += num[i].fi;
				if(!uno || (uno * ratio.se) % ratio.fi != 0) continue;
				lli needed = (uno * ratio.se) / ratio.fi;
				if(act <= needed && dos >= needed && uno*ratio.se >= ratio.fi) {
					dos = dos - needed;
					uno = 0;
					ans++;
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
