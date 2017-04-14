#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<lli,lli>
#define psi pair<lli,pii>
#define fi first
#define se second
#define pb(a) push_back(a)

using namespace std;

const int MAXN = 1005;

lli w;
pii num[MAXN];
lli dist[MAXN][2];

lli Dist(int i,int j) {
	if(i == j) return 0;
	if(num[i].fi == 0 || num[i].fi == w || num[j].fi == 0 || num[j].fi == w) 
		return (num[i].fi - num[j].fi) * (num[i].fi - num[j].fi);
	return (num[i].fi - num[j].fi) * (num[i].fi - num[j].fi) +
		(num[i].se - num[j].se) * (num[i].se - num[j].se);
}

void Dijsktra(int s, int n,int f) {
	forn(i, n) dist[i][f] = 1LL<<60;
	priority_queue<pii, vector<pii>, greater<pii> > q;

	dist[s][f] = 0;
	q.push(pii(0, s));

	while(!q.empty()) {
		int u = q.top().se;
		lli d = q.top().fi;
		q.pop();

		if(dist[u][f] < d) continue;

		forn(v, n) {
			lli d2 = Dist(u, v);
			if(max(d, d2) < dist[v][f]) {
				dist[v][f] = max(d, d2);
				q.push(pii(dist[v][f], v));
			}
		}
	}
}

double GenX(int i,int j) {
	return (num[i].fi + num[j].fi) / 2.0;
}

double GenY(int i,int j) {
	if(num[i].se == 0) num[i].se = num[j].se;
	else if(num[j].se == 0) num[j].se = num[i].se;
	else if(num[i].se == w) num[i].se = num[j].se;
	else if(num[j].se == w) num[j].se = num[i].se;
	return (num[i].se + num[j].se) / 2.0;
}

int main() {
	//freopen("froggy.in", "r", stdin);
	//freopen("froggy.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout<<fixed<<setprecision(12);
	int n;
	while(cin>>w>>n) {
		forn(i, n)
			cin>>num[i].fi>>num[i].se;
		num[n].fi = 0, num[n++].se = 0;
		num[n].fi = w, num[n++].se = 0;

		Dijsktra(n - 2, n, 0);
		Dijsktra(n - 1, n, 1);

		double maxi = 1LL<<60;
		int a = 0, b = 1;
		forn(i, n)
		forn(j, n) {
			double aux = max((double) dist[i][0], 
				max((double) dist[j][1], Dist(i, j) / 4.0));
			if(aux < maxi) {
				maxi = aux;
				a = i, b = j;
			}
		}

		cout<<GenX(a, b)<<" "<<GenY(a, b)<<endl;
	}
	return 0;
}
