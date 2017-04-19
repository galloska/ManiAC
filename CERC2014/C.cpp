#include <bits/stdc++.h>
#define lli long long int
#define endl '\n'

using namespace std;

int main() {
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        int t;
        lli n;
        cin>>t;
        while(t--) {
                cin>>n;
                lli ini = -1, len;
                for(int i=2;(i * i + i) / 2 <= n;i++) {
                        double aux = n / (i * 1.0) - i / 2.0 - 0.5;
                        lli a = aux;
                        if( fabs(aux - a) < 1e-9 ) {
                                ini = a + 1;
                                len = i;
                                break;
                        }
                }
                if(ini == -1) cout<<"IMPOSSIBLE"<<endl;
                else {
                        cout<<n<<" =";
                        for(int i=0;i<len;i++) {
                                if(i) cout<<" +";
                                cout<<" "<<i + ini;
                        }
                        cout<<endl;
                }
        }
        return 0;
}
