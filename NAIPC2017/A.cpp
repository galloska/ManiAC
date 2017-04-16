#include <bits/stdc++.h>
using namespace std;

int n;
vector<string> data;
vector<int> balance, total, posi, nega, MINIS;

int const INF = 1e8;

int memo[307][90007];

int dp(int idx, int v) {
    if (v < 0)
        return -INF;

    int &r = memo[idx][v];
    if (r != -(1<<30))
        return r;

    if (idx == n)
        return r = ((v == 0)? 0: -INF);

    int peso = MINIS[ total[idx] ];
    int ans = -INF;
    if (v >= abs(peso))
        ans = dp(idx + 1, v - abs(peso) + (balance[ total[idx] ] + abs(peso))) + data[ total[idx] ].size();
    
    return r = max(ans, dp(idx + 1, v));
}

bool compare(const int &i, const int &j) {
    return (balance[i] + abs(MINIS[i])) > (balance[j] + abs(MINIS[j]));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    data    = vector<string>(307);
    balance = vector<int>(307);
    MINIS   = vector<int>(307);
    total   = vector<int>(307);
    posi    = vector<int>(307);
    nega    = vector<int>(307);

    while (cin >> n) {
        for (int i = 0; i < n + 3; ++i)
            for (int j = 0; j < 300 * 300 + 3; ++j)
                memo[i][j] = -(1<<30);

        int contN, contP;
        contN = contP = 0;
        for (int i = 0; i < n; ++i) {
            cin >> data[i];
            
            int open  = 0;
            int close = 0;
            int mini  = 0;
            for (const auto &var : data[i]) {
                open  += (var == '(');
                close += (var == ')');
                mini = min(mini, open - close);
            }
            balance[i] = open - close;

            MINIS[i] = mini;

            if (mini < 0)   nega[contN++] = i;
            else            posi[contP++] = i;
        }
        
        int cont = 0;

        sort(nega.begin(), nega.begin() + contN, compare);

        for (int i = 0; i < contP; ++i) total[cont++] = posi[i];            
        for (int i = 0; i < contN; ++i) total[cont++] = nega[i];            

        
        /*
        for (int i = 0; i < n; ++i) {
            cout << data[ total[i] ] << ' ' << balance[ total[i] ] << ' ' << abs(MINIS[ total[i] ]) << endl;
        }
        */

        cout << dp(0, 0) << '\n';

    }
    return 0;
}
