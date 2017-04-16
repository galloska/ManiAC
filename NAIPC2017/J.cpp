#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define fi first
#define se second
#define pb(a) push_back(a)

using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  string s;
  cin >> s;
  int cntw = 0;
  int cntb = 0;
  
  for (auto & c: s)
    cntw += c == 'W',
    cntb += c == 'B';
    
    
  cout << (cntw == cntb) << '\n';
  
  return 0;
}
