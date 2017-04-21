#include <iostream>
#include <map>

using namespace std;

typedef pair<int, int> pii;
typedef pair<int, pii> p3i;

#define position(p) pii(p.fst, p.snd.fst)
#define snd second
#define fst first


const p3i bad = p3i(-1, pii(-1, -1));
const int Max = 1E8;
const int A   = 250;
const int B   = 450;
const int C   = 9E6;
const int K   =   4;

map<int, int> mi;
map<int, int> mj;

char data[A][A];
int  last[K][B];
pii  list[C];
int  pref[C];

string s;
int n, m;


int is[K] = { 0, -1, 0, 1};
int js[K] = {-1,  0, 1, 0};


p3i nxt(p3i cur) {

  if (cur == bad)
    return bad;

  int curi = cur.fst;
  int curj = cur.snd.fst;
  int curx = cur.snd.snd;
  int nxtx = Max;

  for (int k = 0; k < K; k++) {
    int nxti = curi + is[k];
    int nxtj = curj + js[k];
    if (data[nxti][nxtj] != '#')
      nxtx = min(nxtx, last[k][curx]);
  }

  if (nxtx == Max)
    return bad;

  int nxti = curi + mi[s[nxtx % s.size()]];
  int nxtj = curj + mj[s[nxtx % s.size()]];

  return p3i(nxti, pii(nxtj, (nxtx + 1) % s.size()));
}


int search(int u, int v) {

  p3i slow = p3i(u, pii(v, 0));
  p3i fast = p3i(u, pii(v, 0));

  while (true) {

    slow = nxt(slow); fast = nxt(nxt(fast));

    if (fast == bad)
      return 1;


    if (fast == slow) {

      int idx = 0, k = 0; slow = nxt(slow); list[idx++] = position(slow);

      // KMP

      while (slow != fast) {

        k = pref[idx - 1];
        slow  = nxt(slow);
        list[idx++] = position(slow);

        while (true) {
          if (list[idx - 1] == list[k]) {
            pref[idx - 1] = k + 1;
            break;
          }
          else if (k == 0) {
            pref[idx - 1] = 0;
            break;
          }
          else
            k = pref[k - 1];
        }
      }

      int ans = idx - pref[idx - 1];

      return idx % ans == 0 ? ans : idx;
    }
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  mi['<'] =  0;  mj['<'] = -1;
  mi['^'] = -1;  mj['^'] =  0;
  mi['>'] =  0;  mj['>'] =  1;
  mi['v'] =  1;  mj['v'] =  0;

  for (int i = 0; i < A; i++)
    fill(data[i], data[i] + A, '#');

  string t;
  int u, v;
  cin >> n;
  cin >> s;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> data[i][j];
      if (data[i][j] == 'R')
        u = i, v = j, data[i][j] = '.';
    }
  }

  t = s + s;

  for (int i = 0; i < K; i++)
    last[i][t.size()] = Max;

  for (int i = t.size() - 1; i >= 0; i--) {
    if (t[i] == '<') last[0][i] = i; else last[0][i] = last[0][i + 1];
    if (t[i] == '^') last[1][i] = i; else last[1][i] = last[1][i + 1];
    if (t[i] == '>') last[2][i] = i; else last[2][i] = last[2][i + 1];
    if (t[i] == 'v') last[3][i] = i; else last[3][i] = last[3][i + 1];
  }

  cout << search(u, v) << '\n';

  return 0;
}
