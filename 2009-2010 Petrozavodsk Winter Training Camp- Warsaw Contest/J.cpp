#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define pb(a) push_back(a)
#define B 31
#define pii pair<int,int>
#define fi first
#define se second

using namespace std;

const int MAXN = 1000001;

int ans[MAXN];
int last[MAXN];
int total[MAXN];
string cad[MAXN];

lli hash(const string& s) {
	lli h = 0;
	for(int i=s.size()-1;i>=0;i--)
		h = h * B + s[i];
	return h;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,m,a,b,l,r,id;
	cin>>n>>l>>m;

	vector<lli> H, sale, entra;
	forn(i, n) {
		cin>>cad[i];
		H.pb( hash(cad[i]) );
		entra.pb( hash(cad[i]) );
	}

	vector<pii> aux;
	forn(i, m) {
		cin>>a>>l>>b>>r;
		a--,b--;
		l--,r--;
		aux.pb(pii(a, b));

		sale.pb( hash(cad[a]) );
		if(a != b) sale.pb( hash(cad[b]) );

		swap(cad[a][l], cad[b][r]);

		entra.pb( hash(cad[a]) );
		if(a != b) entra.pb( hash(cad[b]) );

		H.pb( hash(cad[a]) );
		if(a != b) H.pb( hash(cad[b]) );
	}
	sort(H.begin(), H.end());

	a = 0, b = 0;
	forn(i, n) {
		id = lower_bound(H.begin(), H.end(), entra[b++]) - H.begin();
		last[i] = id;
		total[id]++;
	}

	forn(i, n) {
		ans[i] = max(ans[i], total[ last[i] ]);
	}

	forn(i, m) {
		id = lower_bound(H.begin(), H.end(), sale[a++]) - H.begin();
		total[id]--;
		if(aux[i].fi != aux[i].se) {
			id = lower_bound(H.begin(), H.end(), sale[a++]) - H.begin();
			total[id]--;
		}

		id = lower_bound(H.begin(), H.end(), entra[b++]) - H.begin();
		total[id]++;
		last[ aux[i].fi ] = id;

		if(aux[i].fi != aux[i].se) {
			id = lower_bound(H.begin(), H.end(), entra[b++]) - H.begin();
			total[id]++;
			last[ aux[i].se ] = id;
		}

		forn(j, n) {
			ans[j] = max(ans[j], total[ last[j] ]);
		}
	}

	forn(i, n)
		cout<<ans[i]<<endl;
	return 0;
}
