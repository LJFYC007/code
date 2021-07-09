# include <bits/stdc++.h>
using namespace std;
namespace Base{
	# define mr make_pair
	typedef long long ll;
	typedef double db;
	const int inf = 0x3f3f3f3f, INF = 0x7fffffff;
	const ll  infll = 0x3f3f3f3f3f3f3f3fll, INFll = 0x7fffffffffffffffll;
	template<typename T> void read(T &x){
    	x = 0; int fh = 1; double num = 1.0; char ch = getchar();
		while (!isdigit(ch)){ if (ch == '-') fh = -1; ch = getchar(); }
		while (isdigit(ch)){ x = x * 10 + ch - '0'; ch = getchar(); }
	    if (ch == '.'){
	    	ch = getchar();
	    	while (isdigit(ch)){num /= 10; x = x + num * (ch - '0'); ch = getchar();}
		}
		x = x * fh;
	}
	template<typename T> void chmax(T &x, T y){x = x < y ? y : x;}
	template<typename T> void chmin(T &x, T y){x = x > y ? y : x;}
}
using namespace Base;

const int N = 300010, Pout = 998244353;
const int P = 1e9 + 7, GP = 10001, Q = 1e9 + 9, GQ = 10007;
int num[N], fg[N], n, k, lenl, lenr, len, tol, tor;
int p[2][N], preP[2][N], preQ[2][N], sufP[2][N], sufQ[2][N], ths[N], invq[N], invp[N];
int npreP[N], npreQ[N], nsufP[N], nsufQ[N];
int Kout[N], Gp[N], Gq[N];

int power(int x, int k, int P){
	int i = x; x = 1;
	while (k > 0){
		if (k % 2 == 1) x = 1ll * x * i % P;
		i = 1ll * i * i % P;
		k /= 2;
	}
	return x;
} 

int getnum(int id){
	if (lenr >= id) return p[tor][lenr - id + 1];
		else id -= lenr;
	if (lenl >= id) return p[tol][id];
		else id -= lenl;
	return ths[id];
}

void print(int C){
	int sum = 0;
	for (int i = 1; i <= n; i++)
		sum = (sum + 1ll * getnum(i) * Kout[i - 1]) % Pout;
	printf("%d\n", sum);
}

bool check(int l){
	int now1p = 0, now1q = 0, now2p = 0, now2q = 0;
	int las = l;
	
	if (lenr >= l){
		now1p = 1ll * (sufP[tor][lenr] - sufP[tor][lenr - l] + P) % P * invp[lenr - l] % P;
		now1q = 1ll * (sufQ[tor][lenr] - sufQ[tor][lenr - l] + Q) % Q * invq[lenr - l] % Q;
	}
	else {
		now1p = 1ll * sufP[tor][lenr] * Gp[l - lenr] % P;
		now1q = 1ll * sufQ[tor][lenr] * Gq[l - lenr] % Q;
		l -= lenr;
		if (lenl >= l){
			now1p = (preP[tol][l] + now1p) % P;
			now1q = (preQ[tol][l] + now1q) % Q;
		}
		else {
			now1p = (1ll * preP[tol][lenl] * Gp[l - lenl] + now1p) % P;
			now1q = (1ll * preQ[tol][lenl] * Gq[l - lenl] + now1q) % Q;
			l -= lenl;
			now1p = (now1p + npreP[l]) % P;
			now1q = (now1q + npreQ[l]) % Q;
		}
	}
	
	l = las;
	if (len >= l){
		now2p = 1ll * (nsufP[len] - nsufP[len - l] + P) % P * invp[len - l] % P;
		now2q = 1ll * (nsufQ[len] - nsufQ[len - l] + Q) % Q * invq[len - l] % Q;
	}
	else {
		now2p = 1ll * nsufP[len] * Gp[l - len] % P;
		now2q = 1ll * nsufQ[len] * Gq[l - len] % Q;
		l -= len;
		if (lenr >= l){
			now2p = (1ll * (sufP[tor][l] - sufP[tor][lenr - l] + P) % P * invp[lenr - l] + now2p) % P;
			now2q = (1ll * (sufQ[tor][l] - sufQ[tor][lenr - l] + Q) % Q * invq[lenr - l] + now2q) % Q;
		}
		else {
			now2p = (1ll * sufP[tor][lenr] * Gq[l - lenr] + now2p) % P;
			now2q = (1ll * sufQ[tor][lenr] * Gq[l - lenr] + now2q) % Q;
			l -= lenr;
			now2p = (now2p + preP[tol][l]) % P;
			now2q = (now2q + preQ[tol][l]) % Q;
		}
	}
	
	if (now1p == now2p && now1q == now2q) return true;
		else return false;
}

void getnext(){
	int tot = lenl + lenr + len;
	
	for (int i = 1; i <= len; i++){
		npreP[i] = (1ll * npreP[i - 1] * GP + ths[i]) % P;
		npreQ[i] = (1ll * npreQ[i - 1] * GQ + ths[i]) % Q; 
		nsufP[i] = (nsufP[i - 1] + 1ll * ths[i] * Gp[i - 1]) % P;
		nsufQ[i] = (nsufQ[i - 1] + 1ll * ths[i] * Gq[i - 1]) % Q;
	}
	
	int pl = 1, pr = tot, d = 0;
	while (pl <= pr){
		int mid = (pl + pr) / 2;
		if (check(mid)) d = mid, pl = mid + 1;
			else pr = mid - 1;
	} 
	bool flag = 0;
	if (d == tot) flag = 1;
		else {
			int a = getnum(d + 1), b;
			if (d + 1 <= len) b = ths[len - d];
				else b = getnum(d + 1 - len);
			if (a < b) flag = 1; else flag = 0;
		}
		
	if (flag){
		for (int i = 1; i <= len; i++){
			p[tol][++lenl] = ths[i];
			preP[tol][lenl] = (1ll * preP[tol][lenl - 1] * Gp[1] + ths[i]) % P;
			sufP[tol][lenl] = (sufP[tol][lenl - 1] + 1ll * ths[i] * Gp[lenl - 1]) % P;
			preQ[tol][lenl] = (1ll * preP[tol][lenl - 1] * Gq[1] + ths[i]) % Q;
			sufQ[tol][lenl] = (sufP[tol][lenl - 1] + 1ll * ths[i] * Gq[lenl - 1]) % Q;
		}
	}
	else {
		for (int i = 1; i <= len; i++){
			p[tor][++lenr] = ths[i];
			preP[tor][lenr] = (1ll * preP[tor][lenr - 1] * Gp[1] + ths[i]) % P;
			sufP[tor][lenr] = (sufP[tor][lenr - 1] + 1ll * ths[i] * Gp[lenr - 1]) % P;
			preQ[tor][lenr] = (1ll * preQ[tor][lenr - 1] * Gq[1] + ths[i]) % Q;
			sufQ[tor][lenr] = (sufQ[tor][lenr - 1] + 1ll * ths[i] * Gq[lenr - 1]) % Q;
		}
	}
}

int main(){
	freopen("reverse.in", "r", stdin);
	freopen("reverse.out", "w", stdout);
	int op;
	read(op);
	Kout[0] = 1;
	for (int i = 1; i < N; i++) Kout[i] = 1ll * Kout[i - 1] * 37 % Pout;
	
	Gp[0] = 1; Gp[1] = GP;
	for (int i = 2; i < N; i++) Gp[i] = 1ll * Gp[i - 1] * GP % P; 
	invp[0] = 1; invp[1] = power(GP, P - 2, P);
	for (int i = 2; i < N; i++) invp[i] = 1ll * invp[i - 1] * invp[1] % P; 
	
	Gq[0] = 1; Gq[1] = GQ;
	for (int i = 2; i < N; i++) Gq[i] = 1ll * Gq[i - 1] * GQ % Q;  
	invq[0] = 1; invq[1] = power(GQ, Q - 2, Q);
	for (int i = 2; i < N; i++) invq[i] = 1ll * invq[i - 1] * invq[1] % Q; 
	
	for (int opt = 1; opt <= op; opt++){
		read(n), read(k);
		for (int i = 1; i <= n; i++) read(num[i]);
		for (int i = 1; i <= n + 1; i++) fg[i] = false;
		for (int i = 1; i <= k; i++){
			int x; read(x);
			fg[x] = true;
		}
		lenr = 0, lenl = 0, len = 0; tol = 0; tor = 1;
		int i = 1;
		while (true){
			len = 0;
			while (fg[i] == true) ths[++len] = num[i++];
			if (i == n + 1) break;
			ths[++len] = num[i++];
			getnext();
		}
		print(opt);
	}
	return 0;
}


