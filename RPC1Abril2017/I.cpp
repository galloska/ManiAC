#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define pii pair<int,int>
#define fi first
#define se second

using namespace std;

const int MAXN = 3001;

int tim[MAXN];
string name[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t,n,k;
	cin>>t;
	while(t--) {
		cin>>n>>k;
		priority_queue<pii, vector<pii>, greater<pii> > q;
		forn(i, n) {
			cin>>name[i]>>tim[i];
			q.push(pii(tim[i], i));
		}

		while(k--) {
			int id = q.top().se;
			int t = q.top().fi;
			q.pop();
			cout<<t<<" "<<name[id]<<endl;
			q.push(pii(t + tim[id], id));
		}
	}
	return 0;
}
