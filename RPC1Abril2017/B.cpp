#include <bits/stdc++.h>
#define endl '\n'
#define iter vector<int> :: iterator
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<lli,int>
#define fi first
#define se second

using namespace std;

struct Wavelet {
	vector< vector<int> > mapLeft, mapRight;

	Wavelet(vector<int>& A) : mapLeft(A.size() * 2), mapRight(A.size() * 2) {
		build(A.begin(), A.end(), 0, A.size() - 1, 1);
	}

	void build(iter b, iter e, int l,int r,int u) {
		if(l == r) return;
		int med = (l + r) >> 1;

		mapLeft[u].reserve(e - b + 1);
		mapRight[u].reserve(e - b + 1);

		int izq = 0, der = 0;
		mapLeft[u].push_back(0);
		mapRight[u].push_back(0);
		for(iter it=b;it!=e;it++) {
			if(*it <= med) izq++;
			else der++;
			mapLeft[u].push_back(izq);
			mapRight[u].push_back(der);
		}

		iter bound = stable_partition(b, e, [=](int i) { return i <= med; });

		build(b, bound, l, med, u<<1);
		build(bound, e, med + 1, r, (u<<1) + 1);		
	}

	int rank(int q,int i,int l, int r,int u) {
		if(l == r) return i;
		int med = (l + r) >> 1;
		if(q <= med) return rank(q, mapLeft[u][i], l, med, u<<1);
		return rank(q, mapRight[u][i], med + 1, r, (u<<1) + 1);
	}

	int totalLeft(int i,int j,int u) {
		return mapLeft[u][j] - mapLeft[u][i - 1];
	}

	int Kth(int k, int i,int j, int l, int r,int u) {
		if(l == r) return l;
		int med = (l + r) >> 1;
		if(totalLeft(i, j, u) >= k)
			return Kth(k, mapLeft[u][i - 1] + 1, mapLeft[u][j], l, med, u << 1);
		k -= totalLeft(i, j, u);
		return Kth(k, mapRight[u][i - 1] + 1, mapRight[u][j], med + 1, r, (u<<1) + 1);
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,m,l,r,k;
	while(cin>>n>>m) {

		vector<pii> A(n, pii(0, 0));
		map<int,lli> check;
		forn(i, n) {
			cin>>A[i].fi;
			A[i].se = i;
		}
		sort(A.begin(), A.end());

		vector<int> B(n, 0);
		forn(i, n) {
			B[ A[i].se ] = i;
			check[i] = A[i].fi;
		}

		Wavelet tree(B);
		while(m--) {
			cin>>l>>r>>k;
			cout<<check[tree.Kth(k, l, r, 0, n - 1, 1)]<<endl;
		}
	}
	return 0;
}
