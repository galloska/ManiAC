#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<lli,lli>
#define fi first
#define se second
#define pb push_back

using namespace std;

const int MAXN = 1000001;

pii ans[MAXN];
double X[MAXN];
double Y[MAXN];

double Dist(int i,int j) {
	return hypot( X[i] - X[j], Y[i] - Y[j] );
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin>>n;
	lli x,y;

	vector<pii> aux;
	set<int> s;
	n += 2;
	forn(i, n) {
		cin>>x>>y;
		X[i] = x;
		Y[i] = y;
		if(!i || i == n - 1) s.insert(i);
		else aux.pb(pii(y, i));
	}
	n -= 2;

	sort(aux.begin(), aux.end());
	int i = aux.size() - 1;
	while(i >= 0) {
		int j = i;
		vector<int> num;
		while(j >= 0 && aux[j].fi == aux[i].fi) {
			set<int> :: iterator it = s.upper_bound( aux[j].se );
			int next = *it;
			it--;
			int prev = *it;
			ans[ aux[j].se ] = pii( prev, next );
			num.pb( aux[j].se );
			j--;
		}

		i = j;
		forn(h, num.size()) s.insert( num[h] );
	}

	cout<<fixed<<setprecision(4);
	for(int i=1;i<=n;i++) 
		cout<<ans[i].fi<<" "<<ans[i].se<<" "<<Dist(i, ans[i].fi) <<" "<< 
				Dist(i, ans[i].se)<<endl;
	return 0;
}
