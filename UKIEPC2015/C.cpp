#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define psi pair<int,pii>

using namespace std;

#define id(s) (ids.find(s) == ids.end() ? ids[s] = ids.size() : ids[s])

map<string, set<int>> words;
map<string, int> cont;
map<string, int>  ids;




int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, m;
  string s;
  cin >> n;
  
  for (int i = 0; i < n+1; i++) {
    getline(cin,    s);
	stringstream ss(s);
	
	//lcout << s << endl;
	
	ss >> s;
	
	//cout << s << endl;
	
	int nameId = id(s);
   
	//cout << nameId << endl;
	
	while (ss >> s) 
      words[s].insert(nameId), cont[s]++;
  
  }
  
    vector<pair<int, string>> usedby;
	
	for (auto & p: words) {
	  if (p.second.size() == ids.size() - 1)
	    usedby.pb(make_pair(-cont[p.first], p.first));
    }
  
    sort(usedby.begin(), usedby.end());
	
	if (usedby.size() == 0)
      cout << "ALL CLEAR\n";
	
	for (auto i: usedby)
	  cout << i.second << endl;
 

  return 0;
}
