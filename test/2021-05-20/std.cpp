/*
	Problem:	a.cpp
	Time:		2021-05-19 08:25
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#define i64 long long
#define u64 unsigned i64
#define poly vector <int>

using namespace std;
const int maxn = 1 << 9, MOD = 998244353;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

i64 power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		if (b >>= 1) (base *= base) %= MOD;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

inline int deg(const poly &f) {return (int)f.size() - 1;}

int n, k, invs[maxn];
inline void reduce(int &x) {x += x >> 31 & MOD;}
void NTT(poly &f, int n, int flg)
{
	f.resize(n);
	static int R[maxn], a[maxn];
	REP(i, 0, n - 1) a[i] = f[i];
	if (flg < 0) reverse(a + 1, a + n);
	REP(i, 0, n - 1)
	{
		R[i] = (R[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
		if (i < R[i]) swap(a[i], a[R[i]]);
	}
	static int pool[maxn * 3], *cur = pool, *w[30], vis[30];
	for (int i = 1, c = 0; i < n; i <<= 1, c++)
	{
		if (!vis[c])
		{
			vis[c] = 1;
			w[c] = cur;cur += i;
			w[c][0] = 1;const i64 wn = power_pow(3, MOD - 1 >> c + 1);
			REP(l, 1, i - 1) w[c][l] = w[c][l - 1] * wn % MOD;
		}
		for (int k = 0; k < n; k += i + i) for (int l = 0; l < i; l++)
		{
			int x = a[k + l], y = 1ll * a[k + l + i] * w[c][l] % MOD;
			reduce(a[k + l] = x + y - MOD);
			reduce(a[k + l + i] = x - y);
		}
	}
	REP(i, 0, n - 1) f[i] = a[i];
	if (flg < 0)
	{
		const i64 in = inv(n);
		REP(i, 0, n - 1) f[i] = f[i] * in % MOD;
	}
}
const u64 LIM = 17e18;
inline poly operator * (poly f, poly g)
{
	int n = deg(f), m = deg(g), len = 1, c = 0;
	while (len <= n + m) len <<= 1, c++;
	if (len * c > n * m * .5)
	{
		static u64 res[maxn];
		REP(i, 0, n) if (f[i]) REP(j, 0, m) if (g[j])
		{
			res[i + j] += (u64) f[i] * g[j];
			if (res[i + j] >= LIM) res[i + j] %= MOD;
		}
		f.resize(n + m + 1);REP(i, 0, n + m) f[i] = res[i] % MOD, res[i] = 0;
		return f;
	}
	NTT(f, len, 1);NTT(g, len, 1);
	REP(i, 0, len - 1) f[i] = 1ll * f[i] * g[i] % MOD;
	NTT(f, len, -1);f.resize(n + m + 1);
	return f;
}
i64 w = 1;poly f[maxn];
int siz[maxn], hvy[maxn];
void dfs1(int x, int fa = 0)
{
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dfs1(to[i], x);
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
	}
}

void dfs(int x, int fa = 0)
{
	f[x] = poly{1};
	if (hvy[x])
	{
		dfs(hvy[x], x);swap(f[x], f[hvy[x]]);
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && to[i] ^ hvy[x])
		{
			dfs(to[i], x);
			f[x] = f[x] * f[to[i]];
		}
	}
	f[x].resize(siz[x] + 1);
	static int t[maxn];
	REP(i, 1, siz[x]) t[i] = (w * f[x][i - 1] + (siz[x] - i + 1ll) * t[i - 1]) % MOD * invs[i] % MOD;
	REP(i, 1, siz[x]) reduce(f[x][i] += t[i] - MOD);
    cout << x << " "; REP(i, 0, siz[x]) cout << f[x][i] << " "; cout << endl;
}
int ans[maxn];
void init(int n)
{
	invs[0] = invs[1] = 1;
	REP(i, 2, n) invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
}
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
	n = read<int>();k = read<int>();init(n);
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	dfs1(1);
	int len = 1;
	while (len <= n) len <<= 1;
	const i64 wn = power_pow(3, (MOD - 1) / len);
	poly ans(len);
	REP(i, 0, len - 1)
	{
        w = i;
		dfs(1);
		ans[i] = f[1][n];
	}
	REP(i, 0, len - 1) cout << ans[i] << " "; 
	NTT(ans, len, -1);
	i64 Ans = 0;
	REP(i, 1, k) Ans += ans[i];
	cout << Ans % MOD << endl;
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
