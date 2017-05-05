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

    string cad;
    cin >> cad;

    if (cad.size() < 2) {
        if (cad == "1")
            cout << 1 << endl;
        else if (cad == "2")
            cout << 2 << endl;
        else
            cout << 3 << endl;
        return 0;
    }
    
    double acc = 1;
    int tam    = cad.size();

    forn(i, 1000000) {
        if (acc >= tam) {
            cout << i - 1 << endl;
            break;
        }
        acc += log10((double)i);
    }

    return 0;
}
