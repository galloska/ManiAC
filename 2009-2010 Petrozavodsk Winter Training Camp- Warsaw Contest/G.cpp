#include <bits/stdc++.h>

using namespace std;

typedef long long lli;

const lli Inf = 1E18;
const lli A   = 601;
const lli B   =  51;


lli memo[A][A][B];



lli nums[A][A];
lli accm[A][A];
lli rect[A];
lli N;

lli query(lli x, lli y) {
  return rect[y] - rect[x];
}

lli dquery(lli x, lli y) {
  return accm[y - 1][1] - accm[x - 1][y - x + 1];
}

lli mincst(lli idx, lli prv, lli k) {

  if (idx == N + 1 && k != 0)
    return -Inf;

  if (idx == N + 1 && k == 0)
    return 0;

  if (memo[idx][prv][k] != -1LL << 60)
    return memo[idx][prv][k];

  if (k == 0)
    return 0;

  lli ans = mincst(idx + 1, prv, k);

  ans = max(ans, mincst(idx + 1, idx, k - 1) + query(prv, idx) - dquery(prv + 1, idx));

  return memo[idx][prv][k] = ans;
}


vector<lli> ans;

void getans(lli idx, lli prv, lli k) {

  if (idx == N + 1 && k != 0)
    return;

  if (idx == N + 1 && k == 0)
    return;

  if (k == 0)
    return;

  lli notk = mincst(idx + 1, prv, k);
  lli take = mincst(idx + 1, idx, k - 1) + query(prv, idx) - dquery(prv + 1, idx);

  if (notk > take)
    getans(idx + 1, prv, k);
  else {
    ans.push_back(idx);
    getans(idx + 1, idx, k - 1);
  }

}





int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  lli n, k;
  cin >> n;
  cin >> k;
  N = n;

  for (int i = 0; i < A; i++)
    for (int j = 0; j < A; j++)
      fill(memo[i][j], memo[i][j] + B, -1LL << 60);

  for (lli i = 1; i <= n; i++)
    for (lli j = 1; j <= n - i; j++)
      cin >> nums[i][j], accm[i][j] = nums[i][j];

  for (lli i = 1; i <= n; i++)
    for (lli j = 1; j <= n - i; j++)
      accm[i][j] += accm[i][j - 1];


  for (lli i = 1; i <= n; i++)
    rect[i] = accm[i][n - i];

  for (lli i = 1; i <= n; i++)
    rect[i] += rect[i - 1];

  for (lli i = 1; i <= n; i++)
    for (lli j = 1; j <= n - i; j++)
      accm[i][j] += accm[i - 1][j + 1];

  getans(1, 0, k);

  for (lli i = 0; i < ans.size(); i++)
    cout << ans[i] << ' ';
  cout << '\n';

  return 0;
}
