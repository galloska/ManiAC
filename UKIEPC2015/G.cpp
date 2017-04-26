#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define psi pair<int,pii>

using namespace std;

const int MAXN = 10;

int n;
string cad[MAXN];
int costo[MAXN];
int total[MAXN];
int afecta[MAXN];
int percentage[MAXN];
int memo[10][1001][801];

int DP(int id,int dinero,int beber) {
	if(memo[id][dinero][beber] != -1) return memo[id][dinero][beber];
	if(id == n) 
		return memo[id][dinero][beber] = ((dinero == 0) && (beber == 0));
	int ans = 0;
	if(dinero >= costo[id] && beber >= afecta[id])
		ans = DP(id, dinero - costo[id], beber - afecta[id]);

	return memo[id][dinero][beber] = max(ans, DP(id + 1, dinero, beber));
}

void DP2(int id,int dinero,int beber) {
	if(id == n || (!dinero && !beber)) return;
	int ans = 0;
	if(dinero >= costo[id] && beber >= afecta[id] && 
	memo[id][dinero - costo[id]][beber - afecta[id]]) {
		total[id]++;
		DP2(id, dinero - costo[id], beber - afecta[id]);
		return;
	}

	return DP2(id + 1, dinero, beber);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int dinero, beber;
	double a,b,c;
	string aux;
	cin>>a>>b>>n;
	dinero = a * 100;
	beber = b * 10 * 6;

	forn(i, n + 1)
	forn(j, dinero + 1)
	forn(h, beber + 1)
		memo[i][j][h] = -1;

	forn(i, n) {
		cin>>cad[i]>>percentage[i]>>aux>>b;

		costo[i] = b * 100;
		percentage[i] *= 10;

		if(aux == "1/1") afecta[i] = 6 * percentage[i];
		else if(aux == "1/2") afecta[i] = 3 * percentage[i];
		else afecta[i] = 2 * percentage[i];
	}
	if(!DP(0, dinero, beber)) cout<<"IMPOSSIBLE"<<endl;
	else {
		DP2(0, dinero, beber);
		forn(i, n)
			if(total[i])
				cout<<cad[i]<<" "<<total[i]<<endl;
	}
	return 0;
}
