#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define pdd pair<double,double>
#define fi first
#define se second
#define pb push_back

using namespace std;
typedef long long Long;

const int MAXN = 1000001;

const double ERROR = 1e-9;

bool Igual(double a, double b) {
	return fabs(a - b) < ERROR;
}

struct Punto {
	double x, y;

	Punto() : x(), y() {}
	Punto(double X, double Y) : x(X), y(Y) {}

	bool operator<(const Punto& cmp) const{
		if (!Igual(x, cmp.x)) return x < cmp.x;
		return Igual(y, cmp.y)? false: y < cmp.y;
	}

	bool operator==(const Punto & cmp) const {	
		return Igual(x, cmp.x) && Igual(y, cmp.y);
	}
};

double Distancia(const Punto& p, const Punto& q) {
	return hypot(p.x - q.x, p.y - q.y);
}

double Dot(const Punto& v, const Punto& w) {
	return v.x * w.x + v.y * w.y;
}

double Cruz(const Punto& v, const Punto& w) {
	return v.x * w.y - v.y * w.x;	
}

Punto Trasladar(const Punto& o, const Punto& p) {
	return Punto(p.x - o.x, p.y - o.y);
}

int ManoDerecha(const Punto& o, const Punto& p, const Punto& q) {
	double ccw = Cruz(Trasladar(o, p), Trasladar(o, q));
	return Igual(ccw, 0)? 0: (ccw < 0)? -1: 1;
}

struct Linea {
	Punto p, q;
	double a, b, c;

	Linea() : p(), q(), a(), b(), c() {}

	Linea (const Punto& P, const Punto& Q)
		: p(P), q(Q), a(), b(), c() {
		
		if (q < p) swap(p, q);
		a = q.y - p.y;
		b = p.x - q.x;
		if (!a) c = p.y, b = -1;
		else if (!b) c = p.x, a = -1;
		else {
			c = -a*p.x - b*p.y;
		}
	}
};

bool PuntoEnRecta(const Punto& p, const Linea& r) { 
	return !ManoDerecha(r.p, r.q, p);
}

bool PuntoEnSegmento(const Punto& p, const Linea& s) {
	return PuntoEnRecta(p, s) && !(p < s.p || s.q < p);	
}

int InterSegmentos(const Linea& s, const Linea& t) {
	int t1 = ManoDerecha(s.p, s.q, t.p);
	int t2 = ManoDerecha(s.p, s.q, t.q);

	if (t1 == t2) return t1? 0:
		(PuntoEnSegmento(s.p, t) ||
		PuntoEnSegmento(s.q, t) ||
		PuntoEnSegmento(t.p, s) ||
		PuntoEnSegmento(t.q, s))? -1: 0;
	
	return (ManoDerecha(t.p, t.q, s.p) !=
			ManoDerecha(t.p, t.q, s.q))? 1: 0;
}

typedef vector<Punto> Poligono;

double Area(const Poligono& P) {
	double area = 0;
	for (int i = 1; i < P.size(); ++i)
		area += Cruz(P[i - 1], P[i]);
	return fabs(area) / 2.0;
}

bool simple(const Poligono& P) {
	vector< Linea > all;
	forn(i, P.size()) {
		if (i == P.size() - 1) {
			all.pb(Linea(P[i], P[0]));
		} else
			all.pb(Linea(P[i], P[i + 1]));
	}

	int n = all.size();
	forn(i, n) {
		for (int j = i + 2; j < n; ++j) {
			if (i == 0 && j == n - 1) continue;
			if (InterSegmentos(all[i], all[j]))
				return false;
		}
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	while (n--) {
		vector< Punto > data(7);
		forn(i, 7)
			cin >> data[i].x >> data[i].y;

		double p;
		cin >> p;

		vector<int> orden;
		forn(i, 7)
			orden.pb(i);
		
		do {
			Poligono alice;
			forn(i, 7)
				alice.pb(data[ orden[i] ]);
			
			if (!simple(alice)) continue;

			alice.pb(data[ orden[0] ]);
			double a = Area(alice) / 4.0;

			if (p == 0.0 || fabs(a*a*a - p) < 1e-5) { 
				forn(i, 7)
					cout << orden[i] + 1 << ' ';
				cout<<endl;
				break;
			}
		} while (next_permutation(orden.begin(), orden.end()));
	}
	return 0;
}

