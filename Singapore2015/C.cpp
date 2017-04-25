// Association for Computing Machinery

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, p, first;

    cin >> n >> p;
    priority_queue<int, vector<int>, greater<int> > pq;
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        if (i == p)
            first = num;
        else
            pq.push(num);
    }

    int time = 0;
    int ans  = 0;
    int penalty = 0;

    if (first <= 300) {
        ans++;
        penalty += first;
        time += first;

        while (!pq.empty()) {
            int tope = pq.top();
            pq.pop();
            if (time + tope <= 300) {
                ans++;
                penalty += time + tope;
                time += tope;
            } else
                break;
        }
        
        cout << ans << ' ' << penalty << '\n';
    } else
        cout << 0 << ' ' << 0 << '\n';

    return 0;
}
