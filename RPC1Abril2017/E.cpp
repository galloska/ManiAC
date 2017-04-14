#include <bits/stdc++.h>
#define endl '\n'
#define B 31
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<lli,int> 

using namespace std;

const int mod = 1e9 + 7;
const int MAXN = 100001;

string cad;
lli h[MAXN];
lli pot[MAXN];

lli Segment(int ini,int fin) {
	if(ini > fin) return 0ll;
	if(fin == cad.size() - 1) return h[ini];
	return h[ini] - h[fin + 1] * pot[fin - ini + 1];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	pot[0] = 1;
	for(int i=1;i<MAXN;i++) pot[i] = (pot[i - 1] * B) % mod;

	int n,q,l;
	while(cin>>n>>q>>l) {
		map<pii,lli> check;

		forn(i, n) {
			cin>>cad;
			for(int j=l-1;j>=0;j--)
				if(j == cad.size() - 1) h[j] = cad[j];
				else h[j] = (h[j + 1] * B + cad[j]) % mod;
		
			forn(j, l) {
				lli uno = Segment(0, j - 1);
				lli dos = Segment(j + 1, l - 1);
				uno = (uno + (dos * pot[j + 1]) % mod) % mod;
				check[ pii(uno, j) ]++;
			}
		}

		forn(i, q) {
			lli ans = 0;
			cin>>cad;
			for(int j=l-1;j>=0;j--)
				if(j == cad.size() - 1) h[j] = cad[j];
				else h[j] = (h[j + 1] * B + cad[j]) % mod;
		
			forn(j, l) {
				lli uno = Segment(0, j - 1);
				lli dos = Segment(j + 1, l - 1);
				uno = (uno + (dos * pot[j + 1]) % mod) % mod;
				if(check.find(pii(uno, j)) != check.end())
					ans += check[ pii(uno, j) ];
			}
			cout<<ans<<endl;
		}
	}
	return 0;
}
