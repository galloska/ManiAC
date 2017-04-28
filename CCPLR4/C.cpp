#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define psi pair<int,pii>
#define fi first
#define se second
#define pb push_back

using namespace std;

const int MAXN = 101;

int checked[MAXN];
bool vis[2][MAXN];
int mat[MAXN][MAXN];
vector<int> lista[2][MAXN];

vector<int> get(const string& cad) {
	int num = 0, f = 0;
	vector<int> ans;
	forn(i, cad.size()) {
		if(cad[i] == '-') {
			f = 1;
			continue;
		}
		if(cad[i] == ' ') {
			if(num > 0) ans.pb(num);
			num = 0;
		} else num = num * 10 + (cad[i] - 48);
	}
	if(num > 0) ans.pb(num);
	if(f) ans[0] *= -1, ans[1] *= -1;
	return ans;
}

void dfs(int u,int p) {
	vis[p][u] = 1;
	forn(i, lista[p][u].size()) {
		int v = lista[p][u][i];
		if(!vis[p][v]) dfs(v, p);
	}
}

int Can(int u,int t) {
	checked[u] = 1;
	if(vis[0][u]) return 0;
	if(u == t) return 1;
	int ans = 0;
	forn(i, lista[1][u].size()) {
		int v = lista[1][u][i];
		if(!checked[v]) 
			ans = max(ans, Can(v, t));
	}
	return ans;
}

void Solve(int n,int s,int t) {
	dfs(s, 0);
	dfs(t, 1);

	int f = 0;
	forn(i, n)
		if(vis[0][i] && vis[1][i])
			f = 1;
	if(f) cout<<"Y";
	else cout<<"N";

	f = 0;
	forn(i, n) {
		if(i == t) continue;
		forn(j, n) checked[j] = 0;
		if(mat[t][i] && Can(i, t)) f = 1; 
	}
	if(f) cout<<" Y";
	else cout<<" N";
	cout<<endl;
}

void Clear(int n) {
	forn(i, n) {
		forn(j, n)
			mat[i][j] = 0;
		lista[0][i].clear();
		lista[1][i].clear();
		vis[0][i] = 0;
		vis[1][i] = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int c,n,s,t,f,u = 0, caso = 0;
	string cad;
	cin>>c;

	while(getline(cin, cad)) {
		vector<int> ans = get(cad);
		if(!ans.size()) continue;
		if(ans.size() == 3) {
			if(u) {
				if(caso) cout<<endl;
				Solve(n, s, t);
				caso = 1;
			}
			n = ans[0];
			s = ans[1] - 1;
			t = ans[2] - 1;
			f = 1;
			Clear(n);
			u = 1;
		} else {
			if(ans[0] == -1) {
				f = 2;
				continue;
			}
			if(f == 1) lista[0][ans[0] - 1].pb(ans[1] - 1);
			else {
				lista[1][ans[0] - 1].pb(ans[1] - 1);
				mat[ans[0] - 1][ans[1] - 1] = 1;
			}
		}
	}
	if(caso) cout<<endl;
	if(u) Solve(n, s, t);
	return 0;
}
