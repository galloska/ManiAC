// Air Conditioned Minions

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
bool comp(pii &a, pii &b) {
    return a.second < b.second;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector< pair<int, int> > data(n);
    vector<int> left(300);
    map<int, vector<int> > M;

    for (int i = 0; i < n; ++i) {
        cin >> data[i].first >> data[i].second;
        left[ data[i].first ] = 1;
        M[ data[i].first].push_back(i);
    }
    

    sort(data.begin(), data.end(), comp);
    //for (auto var : data)
        //cout << var.first << ' ' << var.second << endl;

    vector<int> used(300);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int j = i;
        while(data[j].first <= data[i].second) j++;
        i = j - 1;
        ans++;      
    }

    cout << ans << '\n';
    return 0;
}
