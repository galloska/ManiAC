#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define pb(a) push_back(a)
#define lli long long int

using namespace std;

typedef complex<double> base;
const double PI = acos(-1.0);
const double ERROR = 0.5;
 
void fft (vector<base> & a, bool invert) {
	lli n = (lli) a.size();
 
	for (int i=1, j=0; i<n; ++i) {
		lli bit = n >> 1;
		for (; j>=bit; bit>>=1)
			j -= bit;
		j += bit;
		if (i < j)
			swap (a[i], a[j]);
	}
 
	for (int len=2; len<=n; len<<=1) {
		double ang = 2*PI/len * (invert ? -1 : 1);
		base wlen (cos(ang), sin(ang));
		for (int i=0; i<n; i+=len) {
			base w (1);
			for (int j=0; j<len/2; ++j) {
				base u = a[i+j],  v = a[i+j+len/2] * w;
				a[i+j] = u + v;
				a[i+j+len/2] = u - v;
				w *= wlen;
			}
		}
	}
	if (invert)
		for (int i=0; i<n; ++i)
			a[i] /= n;
}
 
vector<lli> multiply(const vector<lli> & a, const vector<lli> & b) {
	vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
	size_t n = 1;
	while (n < max (a.size(), b.size()))  n <<= 1;
	n <<= 1;
	fa.resize (n),  fb.resize (n);
 
	fft (fa, false),  fft (fb, false);
	for (size_t i=0; i<n; ++i)
		fa[i] *= fb[i];
	fft (fa, true);
 
	vector<lli> convolucion(n, 0);
	for (size_t i=0; i<n; ++i)
		convolucion[i] = (lli) (fa[i].real() + ERROR);
	return convolucion;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string pattern = "AGCT";
	string uno, dos;
	while(cin>>uno>>dos) {
		vector<lli> A[4], B[4];
		forn(i, 4)
			forn(j, uno.size())
				A[i].pb( (lli) (uno[j] == pattern[i]) );
		forn(i, 4) {
			forn(j, dos.size())
				B[i].pb( (lli) (dos[j] == pattern[i]) );
			reverse(B[i].begin(), B[i].end());
		}

		forn(i, 4)
			A[i] = multiply(A[i], B[i]);

		int maxi = 0, id = 0;
		forn(i, A[0].size()) {
			int val = 0;
			forn(j, 4) val += A[j][i];
			if(val >= maxi) {
				maxi = val;
				id = i;
			}
		}
		cout<<maxi<<endl;
		if(!maxi) {
			cout<<"No matches"<<endl<<endl;
			continue;
		}
		int se = id, fi = dos.size() - 1, ini = 0, ini2 = 0;
		forn(i, dos.size() + uno.size() + dos.size() - 2) {
			char a = '?', b = '?';
			if(fi <= i && ini < uno.size()) a = uno[ini++];
			if(se <= i && ini2 < dos.size()) b = dos[ini2++];
			if(a == '?' && a == b) continue;
			if(a == '?') cout<<b;
			else if(b == '?') cout<<a;
			else if(a == b) cout<<a;
			else cout<<'X';
		}
		cout<<endl<<endl;
	}
	return 0;
}
