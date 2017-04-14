#include <iostream>

using namespace std;


const int Max = 1E6;
const int B   = 500;
const int A   =  50;
const int C   =  15;

int memo[B][A][A][C];
int seen[B][A][A][C];

int num[A][B];
int out[A][B];
int N;
int M;


int mincst(int idx, int ini, int fin, int cur) {

  if (ini > fin || idx >= M)
    return  0;

  if (cur > 9)
    return Max;

  if (ini == fin)
    return num[ini][idx] < cur;

  if (seen[idx][ini][fin][cur] == 1)
    return memo[idx][ini][fin][cur];

  int ans = mincst(idx, ini, fin, cur + 1), cst = 0;

  for (int k = ini; k <= fin; k++) {
    cst += num[k][idx] != cur;
    ans  = min(ans, cst + mincst(idx + 1, ini, k, 0) + mincst(idx, k + 1, fin, cur + 1));
  }

  seen[idx][ini][fin][cur] = 1;
  return memo[idx][ini][fin][cur] = ans;

}


void getans(int idx, int ini, int fin, int cur) {

  if (ini > fin || idx >= M)
    return;

  if (cur > 9)
    return;

  if (ini == fin) {
    if (num[ini][idx] < cur)
      out[ini][idx] = cur;
    return;
  }

  int ans = mincst(idx, ini, fin, cur + 1), cst = 0, kth = -1;

  for (int k = ini; k <= fin; k++) {
    cst += num[k][idx] != cur;
    int res = cst + mincst(idx + 1, ini, k, 0) + mincst(idx, k + 1, fin, cur + 1);
    if (ans > res)
      ans = res, kth = k;
  }

  if (kth < 0)
    getans(idx, ini, fin, cur + 1);
  else {
    for (int i = ini; i <= kth; i++)
      out[i][idx] = cur;
    getans(idx + 1, ini, kth, 0);
    getans(idx, kth + 1, fin, cur + 1);
  }

}


int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  char   x;
  cin >> N;
  cin >> M;

  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++)
      cin >> x, num[i][j] = out[i][j] = x - '0';

  getans(0, 0, N - 1, 0);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++)
      cout << out[i][j];
    cout << '\n';
  }

  return 0;
}
