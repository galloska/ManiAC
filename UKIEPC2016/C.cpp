#include <iostream>
#include <cstdio>
#include <queue>
#include <stack>
#include <cassert>

using namespace std;

typedef pair<int, int> pii;
typedef pair<pii, pii> p4i;

#define se second
#define fi first

const int Max = 1E6; 
const int A   = 257;
const int X   = 256;

int dist[A][A][A];
int whoA[A][A][A];
int whoB[A][A][A];
int whoC[A][A][A];
int oper[A][A][A];


void search(int target) {

  priority_queue<p4i> q;
  whoA[X][X][X] = -1;
  whoB[X][X][X] = -1;
  whoC[X][X][X] = -1;

  dist[X][X][X] = 0; 

  q.push(p4i(pii(0, X), pii(X, X)));

  while (!q.empty()) {

    int curd = q.top().fi.fi; 
    int cura = q.top().fi.se; 
    int curb = q.top().se.fi;
    int curc = q.top().se.se; q.pop();

    if (curd >= 40) continue;

    if (target == cura || target == curb) {
      int cpya = cura;
      stack<string> ins;
      while (whoA[cura][curb][curc] > 0) {
        if (oper[cura][curb][curc] == 1) ins.push("ST A");
        if (oper[cura][curb][curc] == 2) ins.push("ST X");        
        if (oper[cura][curb][curc] == 3) ins.push("PH A");
        if (oper[cura][curb][curc] == 4) ins.push("PH X");
        if (oper[cura][curb][curc] == 5) ins.push("PL A");
        if (oper[cura][curb][curc] == 6) ins.push("PL X");
        if (oper[cura][curb][curc] == 7) ins.push("PH A\nAD");
        if (oper[cura][curb][curc] == 8) ins.push("PH X\nAD");   
        int nxta = whoA[cura][curb][curc];          
        int nxtb = whoB[cura][curb][curc];          
        int nxtc = whoC[cura][curb][curc]; 
        cura = nxta; curb = nxtb; curc = nxtc;         
      }
      while (!ins.empty()) cout << ins.top() << '\n', ins.pop(); cout << "DI" << (target == cpya ? " A" : " X") << '\n';

      return;
    }


    if (dist[1][curb][curc] > 1 + dist[cura][curb][curc]) {
      int nxtd = dist[1][curb][curc] = 1 + dist[cura][curb][curc];
      whoA[1][curb][curc] = cura;
      whoB[1][curb][curc] = curb;
      whoC[1][curb][curc] = curc;
      oper[1][curb][curc] = 1;
      q.push(p4i(pii(nxtd, 1), pii(curb, curc)));
    }
  
    if (dist[cura][1][curc] > 1 + dist[cura][curb][curc]) {
      int nxtd = dist[cura][1][curc] = 1 + dist[cura][curb][curc];
      whoA[cura][1][curc] = cura;
      whoB[cura][1][curc] = curb;
      whoC[cura][1][curc] = curc;
      oper[cura][1][curc] = 2;

      q.push(p4i(pii(nxtd, cura), pii(1, curc)));
    }
   
    if (curc == X) {
      if (cura != X && dist[cura][curb][cura] > 1 + dist[cura][curb][curc]) {
        int nxtd = dist[cura][curb][cura] = 1 + dist[cura][curb][curc];
        whoA[cura][curb][cura] = cura;
        whoB[cura][curb][cura] = curb;
        whoC[cura][curb][cura] = curc;
        oper[cura][curb][cura] = 3;
        q.push(p4i(pii(nxtd, cura), pii(curb, cura)));
      }
      if (curb != X && dist[cura][curb][curb] > 1 + dist[cura][curb][curc]) {
        int nxtd = dist[cura][curb][curb] = 1 + dist[cura][curb][curc];
        whoA[cura][curb][curb] = cura;
        whoB[cura][curb][curb] = curb;
        whoC[cura][curb][curb] = curc;
        oper[cura][curb][curb] = 4;
        q.push(p4i(pii(nxtd, cura), pii(curb, curb)));
      }
    }
    
    if (curc != X) {
      if (dist[curc][curb][X] > 1 + dist[cura][curb][curc]) {
        int nxtd = dist[curc][curb][X] = 1 + dist[cura][curb][curc];
        whoA[curc][curb][X] = cura;
        whoB[curc][curb][X] = curb;
        whoC[curc][curb][X] = curc;
        oper[curc][curb][X] = 5;
        q.push(p4i(pii(nxtd, curc), pii(curb, X)));
      }
      if (dist[cura][curc][X] > 1 + dist[cura][curb][curc]) {
        int nxtd = dist[cura][curc][X] = 1 + dist[cura][curb][curc];
        whoA[cura][curc][X] = cura;
        whoB[cura][curc][X] = curb;
        whoC[cura][curc][X] = curc;
        oper[cura][curc][X] = 6;
        q.push(p4i(pii(nxtd, cura), pii(curc, X)));
      }
      if (cura != X && dist[cura][curb][(curc + cura) & 255] > 2 + dist[cura][curb][curc]) {
        int nxtd = dist[cura][curb][(curc + cura) & 255] = 2 + dist[cura][curb][curc];
        whoA[cura][curb][(curc + cura) & 255] = cura;
        whoB[cura][curb][(curc + cura) & 255] = curb;
        whoC[cura][curb][(curc + cura) & 255] = curc;
        oper[cura][curb][(curc + cura) & 255] = 7;
        q.push(p4i(pii(nxtd, cura), pii(curb, (curc + cura) & 255)));
      }
      if (curb != X && dist[cura][curb][(curc + curb) & 255] > 2 + dist[cura][curb][curc]) {
        int nxtd = dist[cura][curb][(curc + curb) & 255] = 2 + dist[cura][curb][curc];
        whoA[cura][curb][(curc + curb) & 255] = cura;
        whoB[cura][curb][(curc + curb) & 255] = curb;
        whoC[cura][curb][(curc + curb) & 255] = curc;
        oper[cura][curb][(curc + curb) & 255] = 8;
        q.push(p4i(pii(nxtd, cura), pii(curb, (curc + curb) & 255)));
      }
    }       
  }
}


int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int m, n;
  cin >> n;

  for (int i = 0; i < A; i++)
    for (int j = 0; j < A; j++)
      fill(dist[i][j], dist[i][j] + A, Max);
       
  if (n == 0) 
    cout << "ZE A\nDI A\n";
  else
    search(n);

  return 0;
}
