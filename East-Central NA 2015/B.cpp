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

const int MAXN = 117;
int black[MAXN][MAXN];
int white[MAXN][MAXN];

void DEBUG() {
    int tam = 15;
    forn(i, tam) {
        forn(j, tam)
            cout << white[i][j] << ' ';
        cout << endl;
    }
    cout << endl << endl;

    forn(i, tam) {
        forn(j, tam)
            cout << black[i][j] << ' ';
        cout << endl;
    }
}

void BORRA() {
    rep(i, 1, MAXN)
        rep(j, 1, MAXN)
            black[i][j] += black[i][j - 1];

    rep(i, 1, MAXN)
        rep(j, 1, MAXN)
            black[i][j] += black[i - 1][j];

}

void KEEP() {
    rep(i, 1, MAXN)
        rep(j, 1, MAXN)
            white[i][j] += white[i][j - 1];

    rep(i, 1, MAXN)
        rep(j, 1, MAXN)
            white[i][j] += white[i - 1][j];
}


int white_Area(int t, int r, int b, int l) {
    return white[b][r] - white[b][l - 1] - white[t - 1][r] + white[t - 1][l - 1];
}

int black_Area(int t, int r, int b, int l) {
    return black[b][r] - black[b][l - 1] - black[t - 1][r] + black[t - 1][l - 1];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int r, c, n, m;
    cin >> r >> c >> n >> m;
    
    vector<pii> all;
    set<int> hor, ver;

    int acc = 0;
    forn(i, n + m) {
        int a, b;
        cin >> a >> b;

        int x = a + 4;
        int y = b + 7;

        if (x > r || y > c) {
            acc += (i < n);
            continue;
        }

        all.pb(pii(x, y));
        hor.insert(x);
        ver.insert(y);
    }

    if (!n || !m) {
        cout << acc << endl;
        return 0;
    }

    map<int, int> mapX, mapY;
    int cont = 2;
    for (const auto &var: hor)  mapX[var] = cont++;

    cont = 2;
    for (const auto &var: ver)  mapY[var] = cont++;

    rep(i, 0, n - acc) {
        int x = mapX[ all[i].fi ];
        int y = mapY[ all[i].se ];
        black[x][y] = 1;
    }

    rep(i, n - acc, n + m - acc) {
        int x = mapX[ all[i].fi ];
        int y = mapY[ all[i].se ];
        white[x][y] = 1;
    }
    
    //DEBUG();

    BORRA();
    KEEP();

    //DEBUG();

    int ans = n + m - acc;
    int HOR = hor.size() + 7;
    int VER = ver.size() + 7;
    for (int i = 1; i < HOR; ++i) {
        for (int j = 1; j < VER; ++j) {
            for (int k = i; k < HOR; ++k) {
                for (int h = j; h < VER; ++h) {

                    int t = i;
                    int r = h;
                    int b = k;
                    int l = j;

                    int saca = white_Area(t, r, b, l);     
                    int mete = black_Area(1, 105, 105, 1) - black_Area(t, r, b, l);
                    
                    ans = min(ans, saca + mete);
                }
            }
        }
    }
   

    cout << ans + acc << endl;
	return 0;
}

