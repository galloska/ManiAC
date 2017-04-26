#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define forr(i, n) for(int i=n-1;i>=0;i--)
#define pii pair<int,int>
#define lli long long int
#define fi first
#define se second
#define pb push_back

using namespace std;

const int MAXN = 2000001;

double H[MAXN];
double X[MAXN];
double L[MAXN];
double R[MAXN];
double res[2][MAXN];

double Angle(int a,int b) {
        if(a == -1 || b == -1 || H[b] <= H[a]) return M_PI / 2.0;
        return atan2(abs(X[a] - X[b]), H[b] - H[a]);
}

void Solve(int n, int id) {
        vector<int> prev;
        prev.pb(-1);
        forn(i, n) {
                int len = prev.size();
                while(len >= 2 && Angle(i, prev[len - 2]) <= Angle(i, prev[len - 1]))
                        prev.pop_back(), len--;
                res[id][i] = Angle(i, prev[len - 1]);
                prev.pb(i);
        }
}

int main() {
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        cout<<fixed<<setprecision(9);
        int n;
        cin>>n;
        forn(i, n) cin>>X[i]>>H[i];

        Solve(n, 0);
        reverse(X, X + n);
        reverse(H, H + n);
        Solve(n, 1);

        reverse(res[1], res[1] + n);
        forn(i, n)
                cout<<( res[0][i] + res[1][i] ) * 12.0 / M_PI<<endl;
        return 0;
}
