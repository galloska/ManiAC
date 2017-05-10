#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define pb push_back
#define fi first
#define se second

using namespace std;

const int MAXN = 101;

vector< vector<lli> > A, B;

void add(int a,int b) {
    A[a][b]++;
    A[b][a]++;
}

vector< vector<lli> > multiply(const vector< vector<lli> >& A, const vector< vector<lli> >& B) {
    vector< vector<lli> > C(A.size(), vector<lli>(A.size(), 0));
    forn(i, A.size())
    forn(j, A.size())
    forn(k, A.size())
        C[i][j] += A[i][k] * B[k][j];
    return C;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m,s,t,a,b;
    cin>>n>>m>>s>>t;

    A.assign(n, vector<lli>(n, 0));
    while(m--) {
        cin>>a>>b;
        add(a, b);
    }
    B = A;

    forn(i, t - 1) 
        B = multiply(A, B);

    lli ans = 0ll;
    forn(i, n) 
        ans += B[s][i];
    cout<<ans<<endl;
    return 0;
}
