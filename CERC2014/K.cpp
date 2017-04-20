#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

typedef long long lld;

typedef pair<lld, lld> pii;

#define snd second
#define fst first

const lld A = 150100;
const lld B =     10;

lld test[A][B];
lld memo[A][B];
pii nums[A];
lld N;
lld T;

lld maxval(lld idx, lld imp) {
  if (idx == N)
    return 0;

  if (test[idx][imp] == T)
    return memo[idx][imp];

  lld notk = maxval(idx + 1, imp), take;

  if (imp != 0)
    take = min(maxval(idx + 1, imp - 1) - nums[idx].snd, nums[idx].fst - nums[idx].snd);
  else
    take = nums[idx].fst - nums[idx].snd;

  test[idx][imp] = T;
  return memo[idx][imp] = max(take, notk);
}


int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  lld t, k;
  cin >> t;
  for (T = 1; T <= t; T++) {
    lld u, v;

    cin >> N >> k;
    for (lld i = 0; i < N; i++)
      cin >> u >> v, nums[i] = pii(u, v);

    sort(nums, nums + N);

    cout << maxval(0, k) << '\n';

  }
  return 0;
}
