#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define MOD 1000000007

using namespace std;

const int MAXN = 1000006;

lli vis[MAXN];
lli pot[MAXN];
vector<lli> primes;

void Criba(lli N) {
	for(lli i=2;i<=N;i++)
		if(!vis[i]) {
			for(lli j=i;j<=N;j+=i)
				vis[j]++;
			primes.pb(i);
		}

	for(int i=2;i<=N;i++)
		vis[i] += vis[i - 1];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	Criba(MAXN - 1);

	pot[0] = 1;
	for(int i=1;i<MAXN;i++)
		pot[i] = (pot[i - 1] * 2ll) % MOD;

	lli n,x,y;
	while(cin>>n>>x>>y && (n || x || y)) {

		n = y - x;
		cout<<(pot[n - 1] * vis[n]) % MOD<<endl;
	}
	return 0;
}
