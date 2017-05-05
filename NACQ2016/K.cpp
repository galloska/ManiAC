#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=1;i<n;i++)
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
    
    int n;
    cin >> n;
    while (n--) {
        int a, b, c, d, lt, at;
        cin >> a >> b >> c >> d >> lt >> at;
    
        int X, Y, cont = 0;
        forn(i, 10001) {
            int num = lt - i*a;
            int den = c;

            if (den == 0) continue;
            int k = num / den;

            if (k <= 0) continue;

            if (i * a + k*c == lt && i*b + k*d == at)
                cont++, X = i, Y = k;
        }

        if (cont == 1)
            cout << X << ' ' << Y << endl;
        else
            cout << "?\n";

    }
    
    return 0;
}
