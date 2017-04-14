#include <bits/stdc++.h>
#define optimizar_io ios_base::sync_with_stdio(0);cin.tie
using namespace std;

int main(){
	int T;
	int N;
	int suma;
	optimizar_io(0);

	cin >> T; 

	for(int caso = 1 ; caso <= T ; caso++){
		cin >> N ; 

		suma = 0;
		for(int i = 2; i*i <= N ; i++ ){
			if(N%i == 0){
				suma += i;
				if(N/i != i){
					suma += N/i;
				}
			}
		}
		suma ++; 

		if( suma < N ){
			cout << "deficient\n";
		} else if(suma > N ){
			cout << "abundant\n";
		} else {
			cout << "perfect\n";
		}
	}
	return 0;
}
