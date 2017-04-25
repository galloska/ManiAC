#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define psi pair<int,pii>
#define fi first
#define se second
#define pb push_back
#define B 31

using namespace std;

const int MAXN = 100001;
const int LOGMAXN = 20;

void BucketSort(vector<int>& sa,
    const vector<int>& rank, int ranks) {

    vector<int> bucket(ranks, 0);
    vector<int> tmp_sa(sa.size());
    for (int i = 0; i < sa.size(); ++i)
        ++bucket[rank[sa[i]]];

    for (int i = 0, sum = 0; i < ranks; ++i) {
        swap(bucket[i], sum); sum += bucket[i];
    } for (int i = 0; i < sa.size(); ++i)
        tmp_sa[bucket[rank[sa[i]]]++] = sa[i];
    swap(sa, tmp_sa);
}

vector<int> SuffixArray(const string& str) {
    int ranks = 255;
    vector<int> sa(str.size());
    vector<int> nrank(str.size());
    vector<int> rank(str.size(), 0);
    vector<int> tmp_rank(str.size());
    for (int i = 0; i < str.size(); ++i)
        nrank[i] = str[i], sa[i] = i;

    for (int p = 0; true; ++p) {
        BucketSort(sa, nrank, ranks + 1);
        BucketSort(sa,  rank, ranks + 1);

        tmp_rank[0] = ranks = 0;
        for (int i = 1; i < str.size(); ++i)
            if (rank[sa[i]] != rank[sa[i - 1]] ||
                nrank[sa[i]] != nrank[sa[i - 1]])
                 tmp_rank[i] = ++ranks;
            else tmp_rank[i] = ranks;

        if (ranks + 1 == str.size()) break;

        for (int i = 1; i <= 1 << p; ++i)
            nrank[str.size() - i] = 0;
        for (int i = 0; i < str.size(); ++i) {
            int prv = sa[i] - (1 << p);
            if (prv >= 0) nrank[prv] = tmp_rank[i];
            rank[sa[i]] = tmp_rank[i];
        }
    }
    return sa;
}

vector<int> LCP(const string& str,
    const vector<int>& sa) {

    vector<int> lcp(str.size());
    vector<int> plcp(str.size());
    vector<int> phi(str.size(), -1);
    for(int i = 1; i < str.size(); ++i)
        phi[sa[i]] = sa[i - 1];
    
    int len = 0;
    for(int i = 0; i < str.size(); ++i) {
        if (phi[i] == -1) continue;
        for (; str[phi[i] + len] ==
               str[i + len]; ++len) {}
        plcp[i] = len; len = max(len-1, 0);
    }
    for (int i = 0; i < str.size(); ++i)
        lcp[i] = plcp[sa[i]];
    return lcp;
}


vector<int> match;
int logTable[MAXN];
vector<int> suffix;
int M[MAXN][LOGMAXN];
int M2[MAXN][LOGMAXN];

void process() {
	int n = match.size();
	for (int i = 0; i < n; i++)
		M[i][0] = i, M2[i][0] = i;

	for (int j = 1; (1 << j) <= n; j++)
	for (int i = 0; i + (1 << j) - 1 < n; i++) {
		if (match[M[i][j - 1]] <= match[M[i + (1 << (j - 1))][j - 1]])
			M[i][j] = M[i][j - 1];
		else
			M[i][j] = M[i + (1 << (j - 1))][j - 1];

		if (suffix[M2[i][j - 1]] >= suffix[M2[i + (1 << (j - 1))][j - 1]])
			M2[i][j] = M2[i][j - 1];
		else
			M2[i][j] = M2[i + (1 << (j - 1))][j - 1];
	}
}

int query(int i,int j) {
	int k = logTable[j-i+1];
	if(match[ M[i][k] ] <= match[ M[j-(1<<k)+1][k] ])
		return match[M[i][k]];
	return match[M[j-(1<<k)+1][k]];
}

int query2(int i,int j) {
	int k = logTable[j-i+1];
	if(suffix[ M2[i][k] ] >= suffix[ M2[j-(1<<k)+1][k] ])
		return suffix[M2[i][k]];
	return suffix[M2[j-(1<<k)+1][k]];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	for(int i=2;i<MAXN;i++)
		logTable[i] = logTable[i >> 1] + 1;

	int k;
	string cad;
	while(cin>>k && k) {
		cin>>cad;
		cad += '$';
		suffix = SuffixArray(cad);
		match = LCP(cad, suffix);

		process();

		int id = -1, maxi = 0;
		k--;
		if(k)
		forn(i, match.size()) {
			if(i + k - 1 >= match.size()) break;
			int ini = i + k - 1, fin = match.size() - 1;
			int aux = query(i, i + k - 1);
			if(!aux) continue;
			while(ini < fin) {
				int med = (ini + fin) / 2;
				if(query(i, med) == aux) ini = med + 1;
				else fin = med;
			}

			if(query(i, ini) < aux) ini--;
			if(aux > maxi) {
				maxi = aux;
				id = query2(i - 1, ini);
			} else if(aux == maxi) id = max(id, query2(i - 1, ini));
		}

		if(!k) {
			cout<<cad.size() - 1<<" "<<0<<endl;
			continue;
		}

		if(id == -1) cout<<"none"<<endl;
		else cout<<maxi<<" "<<id<<endl;
	}
	return 0;
}
