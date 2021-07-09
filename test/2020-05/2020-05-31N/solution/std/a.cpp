#include<bits/stdc++.h>
#include<iostream>
using namespace std;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	for(; !isdigit(ch); ch = getchar()) if(ch=='-') f=-1;
	for(; isdigit(ch); ch = getchar()) x = (x*10)+(ch^48);
	return x * f;
}

typedef long long ll;

int s[20];
int top;
inline void print(ll &ans) {
	top = 0;
	while(ans) {
		s[++top] = ans%10;
		ans /= 10;
	}
	while(top) 
		putchar(s[top--]+'0');
	putchar('\n');
}

const int MAXN = 10000010;
const ll MOD = 998244353;
ll fac[MAXN], ifac[MAXN], inv[MAXN];
int n;

inline ll qpow(ll a, ll b) {
	ll res = 1;
	while(b) {
		if(b & 1LL) res = res * a % MOD;
		b >>= 1, a = a * a % MOD;
	}
	return res;
}

int main() {
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);

	int Q;
	Q = read();
	ll i;
	fac[0] = 1;
	for(i = 1; i <= 10000000; i++) fac[i] = fac[i-1]*i%MOD;
	ifac[10000000] = qpow(fac[10000000], MOD-2);
	for(i = 10000000; i >= 1; i--) ifac[i-1] = ifac[i]*i%MOD;
	for(i = 1; i <= 10000000; i++) inv[i] = ifac[i]*fac[i-1]%MOD;
	while(Q--) {
		n = read();
		ll ans = 0, np = 1;
		for(i = 1; i <= n+1; i++) {
			ans = (ans+i*(i-1)%MOD*ifac[n-i+1]%MOD*np%MOD)%MOD;
			np = np * inv[n]%MOD;
		}
		ans = ans * fac[n-1]%MOD;
		print(ans);
	}
	return 0;
}
