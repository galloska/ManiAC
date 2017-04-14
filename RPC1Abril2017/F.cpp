#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin>>t;
	while(t--) {
		lli n;
		cin>>n;
		cout<<(n + 1) * (n + 1) - 1<<endl;
	}
	return 0;
}
