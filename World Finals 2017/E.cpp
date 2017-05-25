#include <bits/stdc++.h>
#define endl '\n'
#define Long long long
#define forn(i, n) for(int i = 0; i < n; ++i)
#define rep(i, a, b) for(int i = a; i < b; ++i)
#define pii pair<double, double>
#define fi first
#define se second
#define pb push_back
using namespace std;

double const ERROR = 1e-6;

int n;
double t;
vector< pii > data;

double go(double m) {
    double acc  = 0.0;
    forn(i, n)
        acc += data[i].se / (data[i].fi + m);

    return acc;
}

double bin(double izq, double der) {
    forn(it, 100) {
        double m = (izq + der) / 2.0;

        if (go(m) > t)
            izq = m;
        else
            der = m;
    }

    return (izq + der) / 2.0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> t;

    data = vector< pii >(n);
    
    forn(i, n)
        cin >> data[i].se >> data[i].fi;

    sort(data.begin(), data.end());

    cout << fixed << setprecision(9) << bin(-data[0].fi, 1e10) << endl;
    return 0;
}
