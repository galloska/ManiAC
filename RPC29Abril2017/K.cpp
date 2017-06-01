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
const int LOGMAXN = 20;

int data[MAXN];
int loga[MAXN];
int mat[LOGMAXN][MAXN];
int mat2[LOGMAXN][MAXN];

void pre(int n) {
	forn(i, n) mat[0][i] = mat2[0][i] = i;

	for(int j=1;(1<<j)<=n;j++)
		for(int i=0;i+(1<<(j - 1))<n;i++) {
			if(data[ mat[j - 1][i] ] > data[ mat[j - 1][i + (1<<(j - 1))] ])
				mat[j][i] = mat[j - 1][i];
			else mat[j][i] = mat[j - 1][i + (1<<j - 1)];

			if(data[ mat2[j - 1][i] ] < data[ mat2[j - 1][i + (1<<(j - 1))] ])
				mat2[j][i] = mat2[j - 1][i];
			else mat2[j][i] = mat2[j - 1][i + (1<<j - 1)];
		}
}

int query(int i,int j) { // Maximos
	int l = loga[j - i + 1];
	//cout << i << ' ' << j << ' '  << loga[j - i + 1] << ' '; 
	//cout <<  data[ mat[i][l] ] << ' ';
	//cout << data[ mat[ j - (1<<l) + 1][l] ] << endl;

	if(data[ mat[l][i] ] > data[ mat[l][ j - (1<<l) + 1] ])
		return data[ mat[l][i] ];
	return data[ mat[l][ j - (1<<l) + 1 ] ];
}

int query2(int i,int j) { // Minimos
	int l = loga[j - i + 1];
	if(data[ mat2[l][i] ] > data[ mat2[l][ j - (1<<l) + 1] ])
		return data[ mat2[l][i] ];
	return data[ mat2[l][ j - (1<<l) + 1 ] ];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	loga[0] = loga[1] = 0;
	for(int i=2;i<MAXN;i++) loga[i] = loga[i >> 1] + 1;
	
	int n, w, k;
	while (cin >> n >> k >> w) {
		if (!n && !w && !k)
			break;
			
		forn(i, n)
			cin >> data[i];

		pre(n);

		bool ans = true;
		for (int i = k; i < n && ans; ++i) {
			//cout << query(i - k, i - 1) << endl;
			if (abs(query(i - k, i - 1) - data[k]) > w or
			    abs(query2(i - k, i - 1) - data[k]) > w)
				ans = false;
		}
		cout << (ans? "Yes.\n": "No.\n");
	}

	return 0;
}

