#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define pb push_back
#define fi first
#define se second

using namespace std;

const int MAXN = 1000001;

void rotar(vector< vector<bool> > &data) {
    int n = data.size();
    forn(i, n)
        for (int j = i; j < n; ++j)
            swap(data[i][j], data[j][i]);
    
    forn(i, n)
        reverse(data[i].begin(), data[i].end());
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    
    vector< vector<bool> > data(n, vector<bool>(n));
    vector< vector<char> > ans(n, vector<char>(n, '#'));

    int punto = 0;
    forn(i, n) {
        string s;
        cin >> s;
        forn(j, n) {
            data[i][j] = (s[j] == '.');
            punto += (s[j] == '.');
        }
    }
    
    string cad;
    cin >> cad;

    if (punto*4 != n*n) {
        cout << "invalid grille\n";
        return 0;
    }

    int cont = 0;

    forn(i, 4) {
        forn(i, n)
            forn(j, n) if (data[i][j])
                ans[i][j] = cad[cont++];
        rotar(data);
    }
    
    bool valid = true;
    forn(i, n) {
        forn(j, n) {
            if (ans[i][j] == '#')
                valid = false;
        }
    }


    if (!valid)
        cout << "invalid grille";
    else
        forn(i, n) forn(j, n)
            cout << ans[i][j];
    cout << endl;

    return 0;
}
