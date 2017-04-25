// Association for Control Over Minds

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> tams(500007);
    vector<int> cook(500007);
    vector< vector<int> > data(n);
    for (int i = 0; i < n; ++i) {
        int s;
        cin >> s;

        tams[i + 1] = s;
        data[i].assign(s, 0);
        for (int j = 0; j < s; ++j)
            cin >> data[i][j];
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        set<int> receta; 
        int need = 0;
        int used = 0;
        for (int j = 0; j < data[i].size(); ++j) {
            int pollo = data[i][j];

            if (cook[ pollo ]) {
                used++;
                if (receta.find(cook[ pollo ]) == receta.end())
                    need += tams[ cook[pollo] ], receta.insert(cook[pollo]);
            }
        }

        //cout << need << ' ' << used << endl;
        if (need == used) {
            for (const auto &var : data[i])
                cook[var] = i + 1;
            ans++;
        }
    }

    cout << ans << '\n';
    return 0;
}
