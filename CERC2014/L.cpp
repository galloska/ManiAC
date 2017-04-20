#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

typedef long long lld;


const lld Max = 1E8;
const lld A   = 605;


vector<lld> pts;
lld memo[A][A];
lld test[A][A];
lld xe[A];
lld xo[A];
lld hi[A];
lld N,  T;

lld mincst(lld izq, lld der) {

  if (test[izq][der] == T)
    return memo[izq][der];

  test[izq][der] = T;

  lld cst =  0;
  lld b   = -1;
  lld a   = -1;
  for (lld i = 0; i < N; i++) {
    if (pts[izq] < xo[i] && xe[i] < pts[der] && cst < hi[i]) {
      cst = hi[i];
      a   = xo[i];
      b   = xe[i];
    }
  }


  if (a >= 0 && b >= 0) {

    lld ans = Max;

    a = lower_bound(pts.begin(), pts.end(), a) - pts.begin();
    b = lower_bound(pts.begin(), pts.end(), b) - pts.begin();

    for (lld mid = a; mid <= b; mid++)
      ans = min(ans, mincst(izq, mid) + mincst(mid, der) + cst);

    return memo[izq][der] = ans;
  }

  return memo[izq][der] = 0;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  lld w, t;
  cin >> t;


  for (T = 1; T <= t; T++) {
    cin >> N;
    pts.clear();
    pts.push_back(-Max);
    pts.push_back( Max);
    for (lld i = 0; i < N; i++) {
      cin >> xo[i] >> xe[i] >> hi[i];
      pts.push_back(xo[i]);
      pts.push_back(xe[i]);
    }

    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());

    cout << mincst(0, pts.size() - 1) << '\n';
  }
  return 0;
}
