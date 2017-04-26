#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define forn(i, n) for(int i = 0; i < n; ++i)
#define Long long long
#define pii pair<int, int>
#define fi first
#define se second
#define  pb(a) push_back(a)

void pre(vector<char> &data, vector<char> &base) {
    for (char letra = 'a'; letra <= 'z'; ++letra) {
        int mini =  50;
        char ans = 'b';
        
        for (const auto &var : base)
            if (abs(var - letra) < mini)
                mini = abs(var - letra), ans = var;
        
        data[ letra ] = ans;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<char> ini = {'b', 'c', 'd', 
                        'g', 'k', 'n', 
                        'p', 't'};

    vector<char> hh  = {'a', 'o', 'u'};

    vector<char> hard(150), fin(150);

    pre(hard, ini);
    pre(fin, hh);

    for (char letra = 'a'; letra <= 'z'; ++letra)
        hard[ toupper(letra) ] = toupper(hard[letra]),
         fin[ toupper(letra) ] = toupper(fin[letra]);

    string s;
    getline(cin, s);
    stringstream ss (s);
    
    bool first = true;
    while (ss >> s) {
        if (!first)
            cout << ' ';
        first = false;

        int hyphen = s.find("-");
        s.erase(remove(s.begin(), s.end(), '-'), s.end());

        s[0] = hard[ s[0] ];
        for (int i = 1; i < s.size(); ++i)
            if (hard[ s[i] ] == s[i] && i >= hyphen && hyphen != -1)
                s[i] = tolower(s[0]);

        if (hard[ s.back() ] == s.back())
            s += fin[ tolower(s.back()) ], s += "h";

        cout << s;
    }
    return 0;
}
