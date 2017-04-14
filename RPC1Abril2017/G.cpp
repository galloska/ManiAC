#include <bits/stdc++.h>
#define optimizar_io ios_base::sync_with_stdio(0);cin.tie
using namespace std;
typedef long long int Long;
const Long mod = (1e9)+7;
const Long inv6 = 166666668LL;
const Long inv2 = 500000004LL;

Long exp(Long a,Long b){
	Long ans = 1LL;
	while(b) {
		if(b & 1LL) ans = (ans * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return ans;
}

Long sum(Long n){
	Long ret;
	ret = (n*(n+1LL))%mod;
	ret = (ret*inv2)%mod;
	return ret;
}

Long f(Long n){
	Long A,B,C;
	Long N = n;
	A = (2LL*N); 
	N = (N*n)%mod;
	B = (3LL*N)%mod;
	N = (N*n)%mod;
	C=  N;
	Long ret = (A+B+C)%mod;
	ret = (ret*inv6)%mod;
	return ret;
}

int main(){
	int T;
	Long N;
	Long P;
	Long A,S;
	Long L,H;
	Long ans;

	optimizar_io(0);
	cin >> T;

	for(int caso = 1 ; caso <= T; caso++){
		cin >> N ; 


		if(N == 1){
			ans = 1;
		} else if(N == 2){
			ans = 5;
		} else {
			H = ((N+1LL)/2LL)%mod;
			L = ((N+2LL)/2LL)%mod;

			A = ( mod + N - H ) %mod;

			S = (sum(A)+1LL)%mod;

			P = (L+1LL)%mod;
						

			ans = (H*S)%mod;
			ans += (sum(H-1LL)*P)%mod;
			ans %= mod;			
			ans = (ans + f(H-2LL))%mod;						
			ans = (ans*L)%mod;
			ans += (H*sum(L-1LL))%mod; 
			ans %= mod;


		}
		cout << "Case #"<<caso << ": " << ans << '\n'; 

	}
	return 0;
}
