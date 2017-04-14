#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int x, y, n;

    cin >> x >> y;
    cin >> n;

    vector<int> all;
    set<int> inicio;
    set<int> s;
    map<int, pair<int, long double> > M;
    
    for (int i = 0; i < n; ++i) {
        int low, upp;
        long double f;
        cin >> low >> upp >> f;
        
        s.insert(low);
        s.insert(upp);

        inicio.insert(low);
        M[low] = make_pair(upp, f);
    }
    
    for (const auto &var : s)
        all.push_back(var);
    
    sort(all.begin(), all.end());

    if (n == 0 || all[0] != 0)
        all.push_back(0);

    if (n == 0 || all.back() != y)
        all.push_back(y);

    sort(all.begin(), all.end());

    /*  
    for (const auto &var : all)
        cout << var << ' ';
    cout << endl;
    */
    
    
    int idx = 0;
    long double factores = 0.0;
    long double normal   = 0.0;

    while (all[idx] != y) {
        //cout << all[idx] << endl;

        if (inicio.find( all[idx] ) == inicio.end()) {
            normal  += all[idx + 1] - all[idx];

            //cout << " not " << normal << endl;
        } else  {
            auto par = M[ all[idx] ];
            //cout << " info " << par.first << ' ' << par.second << endl;
            long double ANCHO = par.first - all[idx];
            factores += (ANCHO) * par.second;

            //cout << "  " << factores << endl;
        }

        idx++;
    }

    cout << fixed << setprecision(6);
    cout << (long double)x / (factores + normal) << '\n';

    return  0;
}
