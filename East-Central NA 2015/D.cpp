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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n, m;
    cin >> n >> m;

    vector< vector<int> > ans(n + 3, vector<int>(m + 3, (1<<30)));
    vector< vector<char> > data(n + 3, vector<char>(m + 3, '.'));
    queue< pii > q;

    for (int i = 1; i <= n; ++i) {
        string cad;
        cin >> cad;
        for (int j = 1; j <= m; ++j) {
            data[i][j] = cad[j - 1];
            if (cad[j - 1] == '.') {
                q.push(make_pair(i, j));
                ans[i][j] = 0;
            }
        }
    }

    forn(i, n + 2) {
        q.push(pii(i, 0));
        q.push(pii(i, m + 1));
        ans[i][0] = 0;
        ans[i][m + 1] = 0;
    }

    forn(i, m + 2) {
        q.push(pii(0, i));
        q.push(pii(n + 1, i));
        ans[0][i] = 0;
        ans[n + 1][i] = 0;
    }

    vector<int> mvI = { 0,  0, 1, -1};
    vector<int> mvJ = { 1, -1, 0,  0};

    int maxi = 0;
    while (!q.empty()) {
        pii top = q.front();
        q.pop();
        int x = top.fi;
        int y = top.se;

        forn(i, 4) {
            int h = x + mvI[i];
            int k = y + mvJ[i];

            if (h < 0 || k < 0) continue;

            if (ans[x][y] + 1 < ans[h][k] && data[h][k] == 'T') {
                ans[h][k] = ans[x][y] + 1;
                q.push(pii(h, k));
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            maxi = max(maxi, ans[i][j]);
        }
    }
    

    int tam = 2;
    if (maxi >= 10)
        tam = 3;

    for (int i = 1; i <=n; ++i) {
        for (int j = 1; j <=m; ++j) {
            string res = to_string(ans[i][j]);
            forn(k, tam - res.size())
                cout << '.';

            if (ans[i][j])
                cout << ans[i][j];
            else
                cout << '.';
        }
        cout << endl;
    }

    return 0;
}
