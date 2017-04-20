#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

typedef long long lld;


int main() {
  ios::sync_with_stdio(0); cin.tie(0);


  freopen("adjustment.out", "w", stdout);
  freopen("adjustment.in" , "r", stdin );
  char   c;
  lld n, m;
  lld x, q;
  cin >> n;
  cin >> m;

  vector<lld> row(n + 1);
  vector<lld> col(n + 1);

  lld rtimes = 0;
  lld rvalue = 0;
  lld ctimes = 0;
  lld cvalue = 0;


  for (lld i = 1; i <= n; i++)
    row[i] = col[i] = i * n + n * (n + 1LL) / 2LL;

  while (m--) {

    cin >> c;
    cin >> x;

    if (c == 'R') {
      if (row[x] == 0) {
        cout << row[x] << '\n';
      }
      else {
        cout << row[x] - rvalue - rtimes * x << '\n';
        row[x]  = 0;
        ctimes += 1;
        cvalue += x;
      }
    }

    if (c == 'C') {
      if (col[x] == 0) {
        cout << col[x] << '\n';
      }
      else {
        cout << col[x] - cvalue - ctimes * x << '\n';
        col[x]  = 0;
        rtimes += 1;
        rvalue += x;
      }
    }

  }

  return 0;
}
