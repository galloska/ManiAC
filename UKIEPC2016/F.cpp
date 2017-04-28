#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define psi pair<int,pii>
#define fi first
#define se second
#define pb push_back

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string cad;
    cin >> cad;
    vector<int> cub(15);

    forn(i, cad.size()) {
        cub[ cad[i] - '0']++;
    }

    int mini = 2000;
    int num = 1;
    for (int i = 1; i < 10; ++i) {
        if (cub[i] < mini)
            mini = cub[i], num = i;
    }

    if (cub[0] < mini) {
        cout << 1;
        forn(i, mini)
            cout << 0;
        cout << '\n';
        return 0;
    }
    
    if (num) {
        forn(i, mini + 1)
            cout << num;
    }
    cout << '\n';

    return 0;
}
