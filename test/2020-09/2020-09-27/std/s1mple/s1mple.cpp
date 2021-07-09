#if 0
2020.03.25

solution is hidden. :)
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator bool () {
		int c = getchar(); while (c != '0' and c != '1') c = getchar();
		return c == '1';
	}
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 19;
bool link[maxn][maxn];
ll Ans[1 << maxn], f[maxn][1 << maxn], g[1 << maxn][maxn];
char s[maxn];

void FWT_or (ll *a, int n) {
	for (int m = 1; m < n; m <<= 1)
		for (int i = 0; i < n; i += m << 1)
			for (int k = i; k < i + m; k ++)
				a[k + m] += a[k];
}

void iFMT (ll *a, int n) {
	for (int m = 1; m < n; m <<= 1)
		for (int i = 0; i < n; i += m << 1)
			for (int k = i; k < i + m; k ++)
				a[k] -= a[k + m];
}

int a[maxn];

int TOT;
ll solve (int n, int p) {
	++ TOT;
	ll res = 0;
	for (int S = 0; S < (1 << n); S ++) {
		ll tmp = __builtin_popcount(unsigned(S)) & 1 ? -1 : 1;
		for (int i = 0; i < p; i ++)
			tmp *= f[a[i]][S];
		res += tmp;
	}
	return n & 1 ? - res : res;
}

int main () {
    freopen("s1mple.in", "r", stdin);
    freopen("s1mple.out", "w", stdout);
	int n = read;
	for (int i = 0; i < n; i ++)
		for (int j = 0; j < n; j ++)
			read(link[i][j]);
	/* int n = read, K = read; */
	/* for (int i = 0; i < n; i ++) */
	/* 	for (int j = 0; j < n; j ++) */
	/* 		link[i][j] = std::abs(i - j) == K; */

	f[0][0] = 1;
	for (int S = 0; S < (1 << n); S ++) {
		int tot = __builtin_popcount(unsigned(S));
		for (int i = 0; i < n; i ++)
			if (S >> i & 1) {
				int T = S ^ (1 << i);
				if (T == 0)
					g[S][i] = 1;
				for (int j = 0; j < n; j ++)
					if (link[i][j])
						g[S][i] += g[T][j];
				f[tot][S] += g[S][i];
			}
		/* if (f[tot][S] > 2) return 1; */
	}

	for (int i = 0; i < n; i ++)
		FWT_or(f[i], 1 << n);

	for (int S = 0; S < (1 << n >> 1); S ++) {
		int p = 1;
		a[0] = 1;
		for (int i = 0; i < n - 1; i ++)
			S >> i & 1 ? ++ a[p - 1] : a[p ++] = 1;
		bool first = 1;
		for (int i = 0; i < p - 1; i ++)
			first &= a[i] >= a[i + 1];
		if (first) Ans[S] = solve(n, p);
		else {
			std::sort(a, a + p, [] (int x, int y) { return x > y; });
			int T = (1 << n) - 1, pre = 0;
			for (int i = 0; i < p; i ++)
				T ^= 1 << (pre += a[i]) >> 1;
			Ans[S] = Ans[T];
		}
	}

	iFMT(Ans, 1 << n >> 1);
	int q = read;
	while (q --) {
		scanf("%s", s);
		int S = 0;
		for (int i = 0; i < n - 1; i ++)
			if (s[i] == '1')
				S ^= 1 << i;
		printf("%lld\n", Ans[S]);
	}
	debug("%d\n", TOT);
}
