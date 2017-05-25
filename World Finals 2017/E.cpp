#include <bits/stdc++.h>
#define endl '\n'
#define Long long long
#define forn(i, n) for(int i = 0; i < n; ++i)
#define rep(i, a, b) for(int i = a; i < b; ++i)
#define pii pair<int, int>
#define fi first
#define se second
#define pb push_back
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, t;
    cin >> n >> t;

    vector<double> d(n), s(n);
    
    forn(i, n)
        cin >> d[i] >> s[i];

    double izq = -1e10, der = 1e10;
    forn(it, 300) {
        double m = (izq + der) / 2.0;
    
        double acc = 0.0;
        forn(j, n) {
            if (s[j] + m < 0)
                acc = 1e10;
            acc += d[j] / (s[j] + m);
        }

        if (acc > t)
            izq = m;
        else
            der = m;
    }

    cout << fixed << setprecision(9) << (izq + der) / 2.0 << endl;

	return 0;
}
