#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define pii pair<int,int>
#define fi first
#define se second
#define pb(a) push_back(a)
#define MOD 1000000007

using namespace std;

const int MAXN = 5001;

int p[MAXN];
vector<lli> primes;

lli power(lli a,lli b) {
	lli ans = 1ll;
	while(b) {
		if(b & 1ll) ans = (ans * a) % MOD;
		a = (a * a) % MOD;
		b /= 2ll;
	}
	return ans;
}

void Criba(lli n) {
	for(lli i=2;i<=n;i++) 
		if(!p[i]) {
			for(lli j=i*i;j<=n;j+=i) p[j] = 1;
			primes.pb(i);
		}
}

lli numDiv(lli n) {
	lli idx = 0, pf = primes[idx], ans = 1ll;
	while(pf * pf <= n) {
		lli power = 0;
		while(n % pf == 0) {
			n /= pf;
			power++;
		}
		ans *= (power + 1);
		if(idx + 1 == primes.size()) break;
		pf = primes[++idx];
	}
	if(n != 1) ans *= 2ll;
	return ans;
}

lli fact[MAXN];
lli divi[MAXN];
lli inv[MAXN];

lli Combina(int n,int k) {
	lli uno = fact[n];
	lli dos = ( inv[k] * inv[n - k] ) % MOD;
	return (uno * dos) % MOD;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	Criba(MAXN - 1);
	forn(i, MAXN) {
		if(!i) fact[i] = 1;
		else fact[i] = ( fact[i - 1] * (lli) i ) % MOD;
		divi[i] = numDiv(i) - 1;
	}
	forn(i, MAXN)
		inv[i] = power(fact[i], MOD - 2);
	int t, n, k;
	cin>>t;
	while(t--) {
		cin>>n>>k;
		lli sum = 0, ans = 1;
		for(int i=2;i<=n;i++) {
			sum += min(divi[i], (lli) k);
			if(divi[i] > k) ans = (ans * Combina(divi[i], k)) % MOD;
		}
		cout<<sum<<" "<<ans<<endl;
	}
	return 0;
}
