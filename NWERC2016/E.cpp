#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define pii pair<int,int>
#define forn(i, n) for(int i=0;i<n;i++)
#define fi first
#define se second

using namespace std;

const int MAXN = 1000001;

pii num[MAXN];

int main() {
    ios_base::sync_with_stdio();
    cin.tie(0);
    int n;
    cin>>n;
    forn(i, n) {
        cin>>num[i].fi;
        num[i].se = i + 1;
    }
    sort(num, num + n);

    int sum = 0;
    forn(i, n-1)
        sum += num[i].fi;
    if(sum < num[n - 1].fi) {
        cout<<"impossible"<<endl;
        return 0;
    }

    cout<<num[n - 1].se;
    forn(i, n - 1)
        cout<<" "<<num[i].se;
    cout<<endl;
    return 0;
}
