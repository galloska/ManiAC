#include <bits/stdc++.h>
#define pb push_back
#define pii pair<int,int>
#define psi pair<int,pii>
#define lli long long int

using namespace std;

const int A = 50;

lli memo[A][8];
int used[A];
vector< vector<int> > pos;
int N;

int findFirstFree(int id, int cur,int x) {
  for (int i = 0; i < 3; i++)
    if ((cur & (x << i)) == 0)
      return i;
  return 3;
}

bool transform(int id, int & nxt, int & cur, int k) {
  int idx = findFirstFree(id, cur, k == 1 ? 3 : 1);

  if (k == 0) {
    if (idx == 3) return false;
    cur |= (1 << idx);
  }
  
  if (k == 1) {
    if (idx >= 2) return false;
    cur |= (3 << idx);
  }
  
  if (k == 2) {
    if(idx == 3) return false;
    if (id + 1 < N && (used[id + 1] & (1 << idx)) != 0) return false;  
 
    cur |= (1 << idx);
    nxt |= (1 << idx);    
  }

  return true;
}



lli count(int idx, int msk) {
  if (idx == N) return msk == 0;
    
  if (memo[idx][msk] >= 0ll)
    return memo[idx][msk];
    
  lli ans = 0;
  
  for (int h = 0; h < pos.size(); h++) {
        int cur = msk;
        int nxt = 0;
        bool valid = true;
        
        for(int j=0;j<pos[h].size();j++) 
            valid &= transform(idx, nxt, cur, pos[h][j]);
            
        if (valid && cur == 7) {
          ans += count(idx + 1, nxt | used[idx + 1]);
        }
     }
  
  return memo[idx][msk] = ans;
}

int main() {
  int    m;
  double x;
  double y;
  
  cin >> N;
  cin >> m;
  
  
  for (int i = 0; i < A; i++)
    fill(memo[i], memo[i] + 8, -1ll);
  
  set< vector<int> > check;
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      for (int k = 0; k < 4; k++) {
          vector<int> s;
          if(i != 3) s.pb(i);
          if(j != 3) s.pb(j);
          if(k != 3) s.pb(k);

          if(check.find(s) == check.end()) {
            check.insert(s);
            pos.pb(s);            
          }
      }
 
  for (int i = 0; i < m; i++) {
    cin >> x >> y, used[int(x)] |= 1 << int(y);
    // cout<<int(x)<<" "<<int(y)<<endl;
  }
  
  cout << count(0, used[0]) << '\n';
  
  return 0;
}
