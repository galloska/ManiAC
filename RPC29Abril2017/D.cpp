#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back

using namespace std;

const int MAXN = 1e5;

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


int P[20];
bool cumple(int n) {
	for (int i = 0; i < primes.size(); ++i)
		if (n % primes[i] == 0 && n != primes[i])
			return false;
	return true;
}

int reves(int n) {
	int r = 0;
	while (n) {
		r = r * 10 + (n % 10);
		n /= 10;
	}
	return r;
}

set<int> s[12];
void cuenta(int n, int pot) {
	Long nuevo;
	if (n > 1e9)
		return;

	for(int i = 1; i <= 9; ++i) {
		nuevo = i * P[pot + 1] + n;
		if (cumple(nuevo)) {
			s[pot + 1].insert(nuevo);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	criba(MAXN);

	P[0] = 1;
	for (int i = 1; i < 10; i++)
		P[i] = P[i - 1] * 10;

	s[0].insert(3);
	s[0].insert(7);

	forn(i, 10) {
		for (auto const &var : s[i])
			cuenta(var, i);
	}

	s[0].insert(2);
	s[0].insert(5);
	
	vector<int> ans;
	forn(i, 10)
		for (auto const &var : s[i])
			if (s[i].find(reves(var)) != s[i].end())
				ans.pb(var);

	int t;
	cin >> t;
	while (t--) {
		int a,b;
		cin >> a >> b;
		
		int l = upper_bound(ans.begin(), ans.end(), b) - ans.begin();
		int r = lower_bound(ans.begin(), ans.end(), a) - ans.begin();
		
		cout << l - r << '\n';
	}

	return 0;
}
