#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back

using namespace std;

const int MAXN = 1000001;

typedef long long Long;

bitset<100010> bs;
vector<int> primes;

void criba(Long tam) {
	bs.set();
	bs[0] = bs[1] = 0;
	for (Long i = 2; i <= tam; ++i) if (bs[i]) {
		for (Long j = i * i; j <= tam; j += i) bs[j] = 0;
		primes.pb((int)i);
	}
}

Long phi(Long N) {
	Long idx = 0, PF = primes[idx], ans = N;
	while (PF * PF <= N) {
		if (N % PF == 0) ans -= ans / PF;
		while (N % PF == 0) N /= PF;
		if (idx + 1 >= primes.size())
			break;
		PF = primes[++idx];
	}
	if (N != 1)
		ans -= ans / N;
	return ans;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	criba(100000);

	int n;
	cin>>n;
	cout << fixed << setprecision(4);
	while(n--) {
		int f;
		cin >> f;
		Long ans = phi(f);
		cout << ans << ' ' << ans / 2.0 << '\n';
	}
	return 0;
}
