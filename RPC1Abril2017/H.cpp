#include <bits/stdc++.h>
#define optimizar_io ios_base::sync_with_stdio(0);cin.tie
using namespace std;
typedef long long int Long;
typedef vector<Long> Lista;
typedef pair<Long,Long> Par;

int main(){

	Long N;
	int T;
	int I;
	Par R;

	vector<Par>C(1000005);
	Lista PN(1000005),PT(1000005),PB(1000005),PI(1000005);

	optimizar_io(0);

	cin >> T; 

	PN[1] = 4;
	PT[1] = 4;
	PB[1] = 2;
	PI[1] = 1;
	C[1] = Par(0,0);

	for(int i = 2 ; i <= 1000000; i ++){
		PN[i] = PN[i-1]+8;
		PT[i] = PT[i-1]+PN[i];
		PB[i] = PB[i-1]+4;
		PI[i] = PI[i-1]+2;
		C[i] = Par(C[i-1].first+2,C[i-1].second-1);
	}

	for(int caso = 1 ; caso <= T ; caso++){

		cin >> N ; 

		I = lower_bound(PT.begin(),PT.end(),N)-PT.begin();

		if(N == PT[I]){
			R = Par( C[I].first +1 ,C[I].second );
		} else {
			N -= PT[I-1];
			R = C[I];
			if(N <= PB[I]){
				R = Par(R.first - N + 1 , R.second );
			} else {
				N -= PB[I];
				R = Par(C[I].first - PB[I] +1, C[I].second);
				if(N <= PI[I]){
					R = Par(R.first + N , R.second + N);
				} else {
					N -= PI[I];
					R = Par(R.first+PI[I],R.second+PI[I]);
					R = Par(R.first + N , R.second - N);
				}
			}

		}

		cout << R.first << ' ' << R.second << '\n';

	}

	return 0;
}
