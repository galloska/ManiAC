#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define fi first
#define se second
#define pii pair<int,int>
#define pb(a) push_back(a)

using namespace std;

const int MAXN = 1000001;

int A[MAXN];
int B[MAXN];

int S(int x, int n) {
    vector<int> uno, dos;
    forn(i, n) {
        if(A[i] > x) uno.pb(A[i]);
        if(B[i] > x) dos.pb(B[i]);
    }

    forn(i, uno.size()) {
        if(i + 1 < uno.size() && uno[i] == uno[i + 1]) {
            i++;
            continue;
        }
        return 0;
    }
    
    forn(i, dos.size()) {
        if(i + 1 < dos.size() && dos[i] == dos[i + 1]) {
            i++;
            continue;
        }
        return 0;
    }

    return 1;
}

int main() {
    ios_base::sync_with_stdio();
    cin.tie(0);
    int n;
    cin>>n;
    forn(i, n)
        cin>>A[i];
    forn(i, n)
        cin>>B[i];

    lli ini = 0, fin = 1e9;
    while(ini < fin) {
        lli med = (ini + fin) / 2ll;
        if(!S(med, n)) ini = med + 1;
        else fin = med;
    }
    cout<<ini<<endl;
    return 0;
}
