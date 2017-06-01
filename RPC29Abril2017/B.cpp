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

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int a,b,c;
	while(1) {
	cin>>a>>b;
	if(!a && !b) break;
	int sum = 0;
	forn(i, a) {
		cin>>c;
		sum += c;
	}
	cout<<b / sum<<endl;
	}
	return 0;
}
