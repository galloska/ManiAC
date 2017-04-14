#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define pii pair<int,int>
#define fi first
#define se second

using namespace std;

int valid[45];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin>>t;
	lli a;
	while(t--) {
		cin>>a;
		lli ans = 0;
		int num = 0;
		for(int i=0;i<5;i++)
			if(a & (1LL<<(31 - i)))
				num ^= (1LL<<(4 - i));

		ans |= (1LL<<num);
		int j = 5, ini = 0;
		for(int i=0;i<31;i++,ini++,j++) {
			if(a & (1LL<<(31 - ini))) num ^= (1<<4);
			num <<= 1;
			if(a & (1LL<<(31 - (j % 32)))) num ^= 1;
			ans |= (1LL<<num);
		}
		if(ans == (1LL<<32) - 1) cout<<"yes"<<endl;
		else cout<<"no"<<endl;
	}
	return 0;
}
