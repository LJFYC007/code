#include <bits/stdc++.h>

#define ll long long
#define uint unsigned

#define debug(...) fprintf(stderr, __VA_ARGS__)

#define SZ(x) ((int)(x).size())
#define pb push_back

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(y < x) x = y;}

template<class T>
inline void read(T &x) {
	char c;int f = 1;x = 0;
	while(((c = getchar()) < '0' || c > '9') && c != '-');
	if(c == '-') f = -1;else x = c - '0';
	while((c = getchar()) >= '0' && c <= '9') x = x * 10 + c - '0';
	x *= f;
}

const int N = 10000, K = 30;
const int MOD = 1000000007;

int n, k;

int fac[K + 9];
int inv[K + 9];
int g[K + 9];
int cnt[N + 9];
int max;

int p[K + 9];
int ans;

int fpm(int a, int b) {
	int ret = 1;
	while(b) {
		if(b & 1) ret = (ll)ret * a % MOD;
		a = (ll)a * a % MOD, b >>= 1;
	}
	return ret;
}

void dp(int m) {
	static int f[K + 9][N + 9] = {0};
	f[0][0] = 1;
	for(int j = 1; j <= m; ++j)
		for(int k = 0; k <= max; ++k)
			f[j][k] = (f[j - 1][k] + (k >= p[j] ? f[j][k - p[j]] : 0)) % MOD;
	int cur = 1;
	for(int i = 1; i <= n; ++i)
		cur = (ll)cur * f[m][cnt[i]] % MOD;
	int a[31] = {0};
	for(int i = 1; i <= m; ++i) a[p[i]]++;
	cur = (ll)cur * fac[k] % MOD;
	for(int i = 1; i <= k; ++i)
		cur = (ll)cur * fpm(fpm(fac[i], a[i]), MOD - 2) % MOD * inv[a[i]] % MOD;
	for(int i = 1; i <= m; ++i)
		cur = (ll)cur * g[p[i]] % MOD;
	(ans += cur) %= MOD;
}

void dfs(int last, int s, int id) {
	if(s == k) {
		dp(id - 1);
		return ;
	}
	if(s + last > k) return ;
	for(int i = last; i <= k - s; ++i)
		p[id] = i, dfs(i, s + i, id + 1), p[id] = 0;
}

int main() {
	freopen("jdt.in", "r", stdin);
	freopen("jdt.out", "w", stdout);
	
	read(n), read(k);
	fac[0] = inv[0] = 1;
	for(int i = 1; i <= k; ++i) {
		fac[i] = (ll)fac[i - 1] * i % MOD;
		inv[i] = fpm(fac[i], MOD - 2);
	}
	g[1] = 1;
	for(int i = 1; i <= k; ++i) {
		g[i] = fac[i - 1];
		if((i - 1) & 1) g[i] = (MOD - g[i]) % MOD;
	}
	for(int i = 1; i <= n; ++i) {
		int t = i;
		for(int j = 2; j <= t; ++j)
			while(t % j == 0) t /= j, cnt[j]++;
	}
	max = *std::max_element(cnt + 1, cnt + n + 1);
	dfs(1, 0, 1);
	std::cout << (ll)ans * inv[k] % MOD << std::endl;

	fclose(stdin);fclose(stdout);
	return 0;
}
