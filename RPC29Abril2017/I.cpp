#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef long long Long;

struct BIT {
	vector<int> arbol;

	BIT(int N) : arbol(N + 1) {}

	Long Query(int a) {
		Long acc = 0;
		while (a > 0)
			acc += arbol[a],
			a   -= a & -a;
		return acc;
	}

	void Actualizar(int a, int v) {
		while (a < arbol.size()) {
			arbol[a] += v;
			a   	 += a & -a;
		}
	}

	Long Rango(int a, int b) {
		return Query(b) - Query(a - 1);
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--) {
		int n, m;
		cin >> n >> m;
		vector< pii > data(m);
		vector<int> all;
		for (int i = 0; i < m; ++i) {
			cin >> data[i].first >> data[i].second;
			all.push_back(data[i].first);
			all.push_back(data[i].second);
		}
		
		sort(all.begin(), all.end());
		all.erase(unique(all.begin(), all.end()), all.end());

		for (int i = 0; i < m; ++i) {
			int a = lower_bound(all.begin(), all.end(), data[i].first)  - all.begin();
			int b = lower_bound(all.begin(), all.end(), data[i].second) - all.begin();
			data[i] = pii(a + 1, b + 1);
		}
		sort(data.begin(), data.end());

		//for (auto var : data)
			//cout << var.first << ' ' << var.second << endl;

		Long ans = 0;
		BIT arbol(all.size() + 7);
		for (int i = 0; i < m; ++i) {
			ans += arbol.Rango(data[i].first + 1, data[i].second);
			arbol.Actualizar(data[i].second, 1);
		}
		cout << ans << '\n';
	}
	return 0;
}

