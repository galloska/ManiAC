#include <iostream>
#include <cassert>
#include <map>

using namespace std;

#define forn(i,n) for(int i=0;i<(int)(n);i++)
#define forsn(i,s,n) for(int i=(s);i<(int)(n);i++)
#define dforn(i,n) for(int i=(n)-1;i>=0;i--)

using namespace std;

typedef long long tint;

inline tint prodlog(tint a,tint b, tint M)
{
    return (__int128(a) * b) % M;
}

tint potlog(tint a,tint b, const tint M)
{
    tint res = 1;
    while (b)
    {
        if (b%2) res = prodlog(res,a, M);
        a = prodlog(a,a,M);
        b /= 2;
    }
    return res;
}

bool primo(tint n)
{
    if (n < 2) return false;
    if (n == 2) return true;
    tint D = n-1, S = 0;
    while (D%2 == 0)
    {
        D /= 2;
        S++;
    }
    // n-1 = 2^S * D
    static const int STEPS = 16;
    forn(pasos,STEPS)
    {
        const tint A = 1 + rand() % (n-1);
        tint M = potlog(A,D,n);
        if (M == 1 || M == (n-1)) goto next;
        forn(k,S-1)
        {
            M = prodlog(M,M,n);
            if (M == (n-1)) goto next;
        }
        return false;
next:;
    }
    return true;
}

// pollard's rho

tint mcd(tint a,tint b) { return (a==0)?b:mcd(b%a,a);}

tint factor(tint n)
{
    static tint A ,B;
    A = 1 + rand() % (n-1);
    B = 1 + rand() % (n-1);
    #define f(x) (prodlog(x,x + B,n) + A)
    tint x = 2, y = 2, d = 1;
    while (d == 1 || d == -1)
    {
        x = f(x);
        y = f(f(y));
        d = mcd(x-y,n);
    }
    return abs(d);
}

map<tint,tint> fact;

void factorize(tint n)
{
    assert(n > 0);
    while (n > 1 && !primo(n))
    {
        tint f;
        do { f = factor(n); } while (f == n);
        n /= f;
        factorize(f);
        for (auto &it : fact)
        while (n % it.first == 0)
        {
            n /= it.first;
            it.second++;
        }
    }
    if (n > 1)
        fact[n]++;
}

int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);
    tint N;
	int t;
	cin>>t;
    while (t--) {
		cin>>N;
        fact.clear();
        factorize(N);
		int f = 0;
        for (auto it : fact) {
            forn(i, it.second) {
				if(f) cout<<" ";
                cout << it.first;
				f = 1;
			}
        }
        cout << "\n";
    }
    return 0;
}
