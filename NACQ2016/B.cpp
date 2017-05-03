#include<bits/stdc++.h>

using namespace std;

int N;

const int B = 200100;
const int A =     33;

double memo[A][A][2];

double pro[A][A][5];
double val[A][A];


int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  cin >> N;

  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= i; j++)
      cin >> val[i][j];


  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= i; j++)
      for (int k = 0; k <= 4; k++)
        cin >> pro[i][j][k];

  for (int k = 0; k <= B; k++) {
    for (int row = 1; row <= N; row++) {
      for (int col = 1; col <= row; col++) {
        
        if (k <= 0)
          memo[row][col][k % 2] = 0;
        else {
          memo[row][col][k % 2] = val[row][col] * pro[row][col][4];

          if (pro[row][col][0] != 0.0)
            memo[row][col][k % 2] += memo[row - 1][col - 1][(k + 1) % 2] * pro[row][col][0];

          if (pro[row][col][1] != 0.0)
            memo[row][col][k % 2] += memo[row - 1][col - 0][(k + 1) % 2] * pro[row][col][1];

          if (pro[row][col][2] != 0.0)
            memo[row][col][k % 2] += memo[row + 1][col + 0][(k + 1) % 2] * pro[row][col][2];

          if (pro[row][col][3] != 0.0)
            memo[row][col][k % 2] += memo[row + 1][col + 1][(k + 1) % 2] * pro[row][col][3];
        }
      }
    }
  }
        
  cout << fixed << setprecision(9) << memo[1][1][B % 2] << '\n';
  return 0;

}


