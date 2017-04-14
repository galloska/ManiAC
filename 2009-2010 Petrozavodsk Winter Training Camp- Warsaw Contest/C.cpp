#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define pb(a) push_back(a)

using namespace std;

const int MAXN = 1000001;

int cont;
lli sum;
lli value;
int A[MAXN];
int B[MAXN];
lli num[MAXN];
int vis[MAXN];
vector<int> lista[MAXN];

inline void dfs(int u) {
	vis[u] = 1;
	cont++;
	sum += num[u];
	value = min(num[u], value);
	forn(i, lista[u].size()) {
		int v = lista[u][i];
		if(!vis[v]) dfs(v);
	}
}

int ReadInt() {
bool minus = false;
int result = 0;
char ch;
ch = getchar();
while (true) {
if (ch == '-') break;
if (ch >= '0' && ch <= '9') break;
ch = getchar();
}
if (ch == '-') minus = true; else result = ch-'0';
while (true) {
ch = getchar();
if (ch < '0' || ch > '9') break;
result = result*10 + (ch - '0');
}
if (minus)
return -result;
else
return result;
}

int main() {
	int n;
	n = ReadInt();
	lli mini = 1LL<<60;
	forn(i, n) {
		num[i] = ReadInt();
		mini = min(mini, num[i]);
	}

	forn(i, n) {
		A[i] = ReadInt();
		A[i]--;
	}

	forn(i, n) {
		B[i] = ReadInt();
		B[i]--;
		lista[B[i]].pb(A[i]);
		lista[A[i]].pb(B[i]);
	}

	lli ans = 0;
	forn(i, n)
		if(!vis[i]) {
			sum = 0;
			cont = 0;
			value = 1LL<<60;
			dfs(i);
			if(cont > 1) 
				ans += min(
					(sum - value) + value * (cont - 1),
					(sum - value) + mini * (cont - 1) + mini * 2ll + 
					value * 2ll
					);
		}
	printf("%lld\n",ans);
	return 0;
}
