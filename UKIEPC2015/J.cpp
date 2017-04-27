#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

typedef pair<int, int> pii;
typedef pair<int, pii> p3i;

#define se second
#define fi first


const int Max = 1E8;
const int Mod = 120;

const int B   = 201;
const int A   =  70;
const int C   =  20;
const int K   =   5;

int a, b;
int u, v;
int k, h;

int  dist[A][A][B];
int  seen[A][A][B];
char data[A][A];
int  size[B];

int us[B][C];
int vs[B][C];

int is[K] = {-1, 0, 1, 0, 0};
int js[K] = {0, -1, 0, 1, 0};

int search() {

  queue<p3i> q;
  dist[a][b][0] = 0;
  q.push(p3i(a, pii(b, 0)));


  if (seen[a][b][0] && (u != a || b != v)) return Max;

  while (!q.empty()) {

    int curu = q.front().fi;
    int curv = q.front().se.fi;
    int curw = q.front().se.se; q.pop();

    for (int i = 0; i < K; i++) {
      int nxtu = curu + is[i];
      int nxtv = curv + js[i];
      int nxtd = (curw + 1) % Mod;

      if (data[nxtu][nxtv] != '#' && dist[nxtu][nxtv][nxtd] > 1 + dist[curu][curv][curw] && (!seen[nxtu][nxtv][nxtd] || nxtu == u && nxtv == v)) {
        dist[nxtu][nxtv][nxtd] = 1 + dist[curu][curv][curw];
        q.push(p3i(nxtu, pii(nxtv, nxtd)));
      }
    }
  }

  int ans = Max;

  for (int i = 0; i < Mod; i++)
    ans = min(ans, dist[u][v][i]);

  return ans;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  char   c;
  int n, m;
  cin >> n;
  cin >> m;

  for (int i = 0; i < A; i++)
    fill(data[i], data[i] + A, '#');

  for (int i = 0; i < A; i++)
    for (int j = 0; j < A; j++)
      fill(dist[i][j], dist[i][j] + B, Max);


  cin >> c >> a >> b >> c;
  cin >> c >> u >> v >> c;

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> data[i][j];

  cin >> k;

  for (int i = 0; i < k; i++) {
    cin >> size[i];
    for (int j = 0; j < size[i]; j++) {
      cin >> c >> us[i][j] >> vs[i][j] >> c;
      if (j != size[i] - 1) us[i][2 * size[i] - j - 2] = us[i][j];
      if (j != size[i] - 1) vs[i][2 * size[i] - j - 2] = vs[i][j];
    }
    size[i] = max(1, 2 * size[i] - 2);
  }

  for (int t = 0; t < Mod; t++) {

    for (int i = 0; i < k; i++) {

      int badu = us[i][t % size[i]];
      int badv = vs[i][t % size[i]];

      for (int j = badu; data[j][badv] != '#'; j++)
        seen[j][badv][t] = true;

      for (int j = badu; data[j][badv] != '#'; j--)
        seen[j][badv][t] = true;

      for (int j = badv; data[badu][j] != '#'; j++)
        seen[badu][j][t] = true;

      for (int j = badv; data[badu][j] != '#'; j--)
        seen[badu][j][t] = true;
    }

  }

  int ans = search();

  if (ans == Max)
    cout << "IMPOSSIBLE\n";
  else
    cout << ans << '\n';

  return 0;
}
