#include <iostream>
#include <cmath>
#include <iomanip>
#include <utility>
#include <algorithm>
#include <vector>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define psi pair<int,pii>

using namespace std;

long double GradARad(long double grd) {
	return (grd * 3.141592654) / 180.0;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	long double n, g;
	cin >> n >> g;
	vector< pair<long double, long double> > data(n);
	for (int i = 0; i < n; ++i) 
		cin >> data[i].first >> data[i].second;
	reverse(data.begin(), data.end());

	long double acc = 0;
	cout << fixed << setprecision(9);
	vector<double> ans;
	for (int i = 0; i < n; ++i) {
		long double dist = data[i].first;
		long double ang  = data[i].second;

		long double a = g * (cos(GradARad(ang)));

		acc += 2.0 * a * dist; 
		ans.pb(sqrt(acc));
	}

	reverse(ans.begin(), ans.end());
	forn(i, ans.size())
		cout<<ans[i]<<endl;
	return 0;
}

