#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define psi pair<int,pii>
#define fi first
#define se second
#define pb push_back

using namespace std;


const int A = 2000;


vector<string> words[A];


bool endmatches(string  s, string  t) {
  
  if (s.size() < t.size())
    return false;
    
  
  //cout <<  s.substr(s.size() - t.size(), s.size()) << endl;
  
  //cout << s.substr(s.size() - t.size(), t.size()) << '-' << t << endl;
    
  return s.substr(s.size() - t.size(), s.size()) == t;
}

string Line() {
    string r = "";
    char a;
    while( (a = getchar()) && a != '\n') r += a;
    return r;   
}


int main() {
  int n, m;
  string s;
  string t;
  string u;
  cin >> s;
  cin >> n;
  Line();
 
  for (int i = 0; i < n; i++) {
    u = Line();
    
    stringstream ss(u);
    
    while (ss >> t)
      words[i].pb(t);
  }
  
  cin >> m;
  Line();
  
  
  for (int i = 0; i < m; i++) {
    u = Line();

    bool possible = false;
  
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < words[i].size(); j++)
        for (int k = 0; k < words[i].size(); k++) {
          if (endmatches(s, words[i][j]) && endmatches(u, words[i][k]))
            possible = true;
        }
    }

    cout << (possible ? "YES" : "NO") << endl;
  }
  
  return 0;
}
