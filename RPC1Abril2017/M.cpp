#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define pii pair<int,int>
#define fi first
#define se second
#define pb(a) push_back(a)

using namespace std;

const int MAXN = 10000001;

int p[MAXN];
vector<lli> primes;

void Criba(lli n) {
	for(lli i=2;i<=n;i++) 
		if(!p[i]) {
			for(lli j=i*i;j<=n;j+=i) p[j] = 1;
			primes.pb(i);
		}
}

lli sumDiv(lli n) {
	lli idx = 0, pf = primes[idx], ans = 1ll;
	while(pf * pf <= n) {
		lli power = 0, aux = pf;
		while(n % pf == 0) {
			n /= pf;
			power++;
			aux *= pf;
		}
		ans *= (aux - 1) / (pf  - 1);
		if(idx + 1 == primes.size()) break;
		pf = primes[++idx];
	}
	if(n != 1) ans *= (n * n - 1) / (n  - 1);
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	Criba(MAXN - 1);
	int t;
	lli n;
	cin>>t;
	while(t--) {
		cin>>n;
		lli s = sumDiv(n) - n;
		if(s < n) cout<<"deficient"<<endl;
		else if(s == n) cout<<"perfect"<<endl;
		else cout<<"abundant"<<endl;
	}
	return 0;
}
