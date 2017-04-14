
#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define accm(i, d, k) (acc[k][d] - acc[k][i - 1])
#define cont(i,    d) (d - i + 1)

typedef long long lld;

const lld A = 5E5;

map<string, lld> ids;
map<string, lld> fam;
vector<lld> acc[A];
lld caught[A];
lld before[A];


struct Sum{
  lld cnt;
  lld sum;
  lld mxn;
  Sum(lld sum = 0, lld cnt = 0, lld mxn = 0): sum(sum), cnt(cnt), mxn(mxn) {}

  Sum operator+(const Sum & that) {
    return Sum(sum + that.sum, cnt + that.cnt, max(mxn, that.mxn));
  }

};

lld mx = 0;

struct Tree {
  Tree * izq, * der;
  lld lazy;
  lld i, d;
  Sum dato;

  Tree(lld i, lld d):  izq(0), der(0), i(i), d(d), dato(), lazy() {}

  Sum build() {
    if (i == d) return dato = Sum();
    lld m = (i + d) >> 1;
    izq = new Tree(i, m + 0);
    der = new Tree(m + 1, d);
    return dato = izq->build() + der->build();
  }

  void propagate(lld k) {
    if (lazy) {
      dato.mxn += lazy;
      dato.cnt += cont(i,    d) * lazy;
      dato.sum += accm(i, d, k) * lazy;
      if (izq) izq->lazy += lazy;
      if (der) der->lazy += lazy;
      lazy = 0;
    }
  }

  Sum update(lld l, lld r, lld k,  lld v) {
    propagate(k);
    if (r <  i || d <  l) return dato;
    if (l <= i && d <= r) {
      dato.mxn += v;
      dato.cnt += cont(i,    d) * v;
      dato.sum += accm(i, d, k) * v;
      if (der) der->lazy += v;
      if (izq) izq->lazy += v;
      return dato;
    }
    return dato = izq->update(l, r, k, v) + der->update(l, r, k, v);
  }

  Sum query(lld l, lld r, lld k) {
    propagate(k);
    if (r <  i || d <  l) return Sum();
    if (l <= i && d <= r) return dato;
    return izq->query(l, r, k) + der->query(l, r, k);
  }


  lld cost(lld k, lld cnt) {

    if (izq) izq->propagate(k);
    if (der) der->propagate(k);

    if (i == d) {
      mx = max(mx, cnt);
      return accm(i, d, k) * cnt;
    }

    if (izq->dato.cnt > cnt)
      return izq->cost(k, cnt);
    else {
      mx = max(mx, izq->dato.mxn);
      return der->cost(k, cnt - izq->dato.cnt) + izq->dato.sum;
    }

  }



};

Tree * trees[A];


lld countEvolutions(lld f, lld candies, lld total) {

  lld lo = 0, hi = trees[f]->query(1, trees[f]->d, f).cnt;

  while (lo < hi) {

    lld mi = (lo + hi + 1) >> 1;

    lld cst = trees[f]->cost(f, mi);
    lld mon = candies + total - 1;

    if (cst > mon)
      hi = mi - 1;
    else
      lo = mi;

  }

  return lo;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  string s;
  lld n, m;
  lld q, t;

  cin >> n;
  for (lld i = 0; i < n; i++) {
    cin >> m;
    acc[i] = vector<lld>(m);
    for (lld j = 1; j < m; j++) {
      cin >> s >> t;
      fam[s] = i;
      ids[s] = j;
      acc[i][j] = t;
    }
    cin  >>  s;
    fam[s] = i;
    ids[s] = 0;
    for (lld j = 1; j < m; j++)
      acc[i][j] += acc[i][j - 1];
    trees[i] = new Tree(1, max(1LL, m - 1LL));
    trees[i]->build();
  }

  vector<lld> times;

  cin >> q;

  lld evolutionsSoFar = 0, ans = 0;

  for (lld w = 1; w <= q; w++) {
    cin >> t >> s;
    times.push_back(t);
    lld d = ids[s];
    lld f = fam[s];
    caught[f] += 1;

    if (d != 0)
      trees[f]->update(d, trees[f]->d, f, 1);


    evolutionsSoFar -= before[f];
    before[f] = countEvolutions(f, caught[f] * 3, caught[f]);
    evolutionsSoFar += before[f];

   lld cnt = times.end() - lower_bound(times.begin(), times.end(), t - 1800 + 1);

    ans = max(ans, 1000 * evolutionsSoFar + cnt * 100 + 100 * q);

  }

  cout << ans << '\n';

  return 0;
}
