#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

int keyboard[4][3] = {  { 1, 2,  3},
                        { 4, 5,  6},
                        { 7, 8,  9},
                        {-1, 0, -1}};

set<int>  nums;

void search(int i, int j, int val) {
        if (i >= 4 || j >= 3 || val > 200) return;
        nums.insert(val);
        if (keyboard[i][j] > 0 || (keyboard[i][j] == 0 && val > 0))
                search(i, j, val * 10 + keyboard[i][j]);
        search(i + 1, j, val);
        search(i, j + 1, val);
}

int main() {
        ios::sync_with_stdio(0);
        cin.tie(0);
        int n;
        cin >> n;
        search(0, 0, 0);

        vector<int> pre(300);
        for (int i = 1; i < 201; i++) {
                int ans = 1e8;
                int dif = 1e8;
                for (auto var: nums)
                        if (abs(var - i) <= dif)
                                ans = var, dif = abs(var - i);
                pre[i] = ans;
        }

        for (int i = 0; i < n; i++) {
                int target;
                cin >> target;
                assert(target <= 200 && target >= 1);
                cout << pre[target] << '\n';
        }
        return 0;
}
