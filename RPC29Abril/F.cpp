#include <iostream>
#include <cmath>

using namespace std;

const int A = 2000;

int memo[A][30];

string s;
int D;

int dist(char a, char b) {
  return min(abs(a - b), 26 - abs(a - b));
}

int DP(int idx,int prev) {
	if(idx == s.size()) return 0;
	if(memo[idx][prev] != -1) return memo[idx][prev];
	int ans = 0;
	if(prev <= s[idx] - 'a') ans = DP(idx + 1, (s[idx] - 'a' + D) % 26) + 1;
	ans = max(ans, DP(idx + 1, prev));
  	return memo[idx][prev] = ans;
}


int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, t;
  cin >> t;
  while (t--) {
    cin >> s >> D;

    for(int i=0;i<s.size();i++)
    	for(int j=0;j<30;j++)
    		memo[i][j] = -1;

    cout << DP(0, 0) << '\n';
  }
  return 0;
}