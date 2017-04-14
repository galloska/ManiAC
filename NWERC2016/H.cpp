#include <bits/stdc++.h>

#define dig(i) (s[i] - '0')

using namespace std;

typedef long long lld;

string s;

lld count(lld idx, lld last) {

  if (idx >= s.size())
    return 1LL;

  lld ans = count(idx + 1LL, last ^ dig(idx));
  
  if (last == dig(idx)) {
    ans += 1LL << (s.size() - idx - 1);
  }
  return ans;
  
}


int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  lld n, m;
  cin >> n;
  cin >> s;
  lld fst = count(0, 1);
  cin >> s;
  lld snd = count(0, 1);
  cout << snd - fst - 1 << '\n';
  return 0;
}
