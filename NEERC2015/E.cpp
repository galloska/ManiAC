#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define fi first
#define se second
#define pb(a) push_back(a)

using namespace std;

const int MAXN = 20;

int mat[MAXN][MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,k,m;
	while(cin>>n>>k) {
		int sum = 0;

		forn(i, MAXN)
			forn(j, MAXN)
				mat[i][j] = 50;

		int maxi = 0;
		forn(i, n) {
			cin>>m;
			forn(j, m) cin>>mat[i][j];
			maxi = max(maxi, m);
		}

		int col = 0;
		while(k && col < maxi) {
			forn(i, n) 
				if(mat[i][col] >= sum) {
					sum += mat[i][col];
					k--;
				}
			col++;
		}

		cout<<sum + k * 50<<endl;
	}
	return 0;
}
