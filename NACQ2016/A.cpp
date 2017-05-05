#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back

using namespace std;

const int MAXN = 1000001;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    map<char, string> M;
    M['a'] = "@";
    M['b'] = "8";
    M['c'] = "(";
    M['d'] = "|)";
    M['e'] = "3";
    M['f'] = "#";
    M['g'] = "6";
    M['h'] = "[-]";
    M['i'] = "|";
    M['j'] = "_|";
    M['k'] = "|<";
    M['l'] = "1";
    M['m'] = "[]\\/[]";
    M['n'] = "[]\\[]";
    M['o'] = "0";
    M['p'] = "|D";
    M['q'] = "(,)";
    M['r'] = "|Z";
    M['s'] = "$";
    M['t'] = "']['";
    M['u'] = "|_|";
    M['v'] = "\\/";
    M['w'] = "\\/\\/";
    M['x'] = "}{";
    M['y'] = "`/";
    M['z'] = "2";

    for (const auto &var : M)
        M[toupper(var.first)] = var.second;

    string cad;
    getline(cin, cad);

    forn(i, cad.size()) {
        if (M.find(cad[i]) == M.end())
            cout << cad[i];
        else    
            cout << M[cad[i]];
    }
    cout << endl;

    return 0;
}
