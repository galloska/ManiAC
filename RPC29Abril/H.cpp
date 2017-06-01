#include <iostream>
#include <cmath>

using namespace std;

typedef long long lld;

lld indexOfLast(lld n) {

  lld last = 0;
  lld curr = 1;
  lld jump = 1;

  while (true) {

    lld nxtn = last == 1ll ? n / 2ll : (n + 1ll) / 2ll;

    //cout << curr << " " << last << " " << jump << " " << nxtn << endl;
    //cout << n << endl;

    if (last == 1ll)
      curr += jump;
    
    if (n % 2ll != 0ll)
      last = !last;
    
    n =  nxtn;
    jump *= 2ll;

    if (n <= 1ll) return curr;

  }

}




int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  lld    n;
  while (cin >> n, n != 0ll)
    cout << indexOfLast(n) << '\n';
  return 0;
}