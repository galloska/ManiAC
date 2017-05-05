#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back

using namespace std;

const int MAXN = 15005;

string cad;
int dp[2][3][MAXN];

int Val(char a,int f = 0) {
    if(f) a = (a == '(' ? ')' : '(');
    if(a == '(') return 1;
    return -1;
}

int DP() {
    int ans;
    dp[cad.size() & 1][2][10000] = 1;
    dp[cad.size() & 1][1][10000] = 1;
    dp[cad.size() & 1][0][10000] = 1;
    for(int id=cad.size()-1;id>=0;id--) 
        for(int st=2;st>=0;st--)
            for(int sum=15000;sum>=10000;sum--) {
                ans = 0;
                if(st == 0) {
                    int aux = sum + Val(cad[id]);
                    if(aux >= 10000)
                        ans = dp[(id + 1) & 1][0][aux];
                    aux = sum + Val(cad[id], 1);
                    if(aux >= 10000)
                        ans = max(ans, dp[(id + 1) & 1][1][aux]);
                }
                if(st == 1) {
                    int aux = sum + Val(cad[id], 1);
                    if(aux >= 10000)
                        ans = dp[(id + 1) & 1][1][aux];
                    aux = sum + Val(cad[id]);
                    if(aux >= 10000)
                        ans = max(ans, dp[(id + 1) & 1][2][aux]);
                }
                if(st == 2 && sum + Val(cad[id]) >= 10000)
                    ans = dp[(id + 1)&1][st][sum + Val(cad[id])];
                dp[id & 1][st][sum] = ans;

            }
    return dp[0][0][10000];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>cad;
    if(DP()) cout<<"possible"<<endl;
    else cout<<"impossible"<<endl;
    return 0;
}
