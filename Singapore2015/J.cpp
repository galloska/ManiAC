#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define pb push_back
#define lli long long int
#define fi first
#define se second
#define pii pair<lli,lli>

using namespace std;

const int MAXN = 1000001;

struct Segment {
    int l,r;
    lli uno[2];
    Segment *left, *right;
    
    Segment(int a,int b): l(a), r(b), left('\0'), right('\0') {}

    void build() {
        uno[0] = uno[1] = 0;
        if(l == r) return;
        int med = (l + r) / 2;
        left = new Segment(l, med);
        right = new Segment(med + 1, r);
        left->build();
        right->build();
    }

    void update(int a,int c) {
        if(a < l || a > r) return;
        if(a <= l && r <= a) {
            int id = (c <= 50);
            if(c > 50) c -= 50;
            uno[id] ^= (1LL<<c);
            return;
        }
        left->update(a, c);
        right->update(a, c);
        uno[0] = left->uno[0] ^ right->uno[0];
        uno[1] = left->uno[1] ^ right->uno[1];
    }

    pii query(int a,int b) {
        if(b < l || a > r) return pii(0, 0);
        if(a <= l && r <= b) return pii(uno[0], uno[1]);
        pii u = left->query(a, b);
        pii v = right->query(a, b);
        return pii(
            u.fi ^ v.fi,
            u.se ^ v.se
        );
    }
};

int cont;
int num[MAXN];
int fin[MAXN];
int inicio[MAXN];
vector<int> lista[MAXN];

void EulerTour(int u) {
    inicio[u] = cont++;
    forn(i, lista[u].size()) {
        int v = lista[u][i];
        EulerTour(v);
    }
    fin[u] = cont++;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,q,a,b;
    cin>>n>>q;
    forn(i, n) cin>>num[i];

    forn(i, n - 1) {
        cin>>a;
        lista[a - 1].pb(i + 1);
    }

    EulerTour(0);

    Segment *tree = new Segment(0, cont);
    tree->build();
    forn(i, n)
        tree->update(inicio[i], num[i]);
    
    while(q--) {
        cin>>a>>b;
        b--;
        if(!a) {
            pii ans = tree->query(inicio[b], fin[b]);
            int r = 0;
            forn(i, 51)
                r += ((ans.fi & (1LL<<i)) > 0) + ((ans.se & (1LL<<i)) > 0);
            cout<<r<<endl;
        }
        else {
            tree->update(inicio[b], num[b]);
            tree->update(inicio[b], a);
            num[b] = a;
        }
    }
    return 0;
}
