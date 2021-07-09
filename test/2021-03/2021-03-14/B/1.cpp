
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <algorithm>
#include <ctime>
#include <vector>
#include <cstring>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 100 + 10;

int n, k, a[maxn][maxn];

namespace bf
{
	bool f[1 << 10][100], g[1 << 10][100];
	int Cnt[1024];
	struct __init__
	{
		__init__()
		{
			REP(i, 1, 1023) Cnt[i] = Cnt[i >> 1] + (i & 1);
		}
	}__INIT__;
	inline int cnt(int x) {return Cnt[x >> 10] + Cnt[x & 1023];}
	inline int upd(int x) {return x >= k ? x - k : x;}
	int main()
	{
		f[0][0] = 1;
		REP(i, 1, n)
		{
			REP(s, 0, (1 << n) - 1) if (cnt(s) == i - 1) REP(j, 0, k - 1)
			{
				g[s][j] = f[s][j];
				f[s][j] = 0;
			}
			REP(s, 0, (1 << n) - 1) if (cnt(s) == i - 1)
			{
				static int ok[maxn];int N = 0;
				REP(j, 1, n) if (!(s >> (j - 1) & 1) && a[i][j] != -1) ok[++N] = j;
				REP(j, 0, k - 1) if (g[s][j]) REP(l, 1, N)
					f[s | (1 << ok[l] - 1)][upd(j + a[i][ok[l]])] = 1;
			}
		}
		puts(f[(1 << n) - 1][0] ? "Yes" : "No");
		return 0;
	}
}
namespace judge
{
	vector <int> G[maxn];
	int mat[maxn];
	bool vis[maxn];
	
	bool match(int x)
	{
		for (int y : G[x]) if (!vis[y])
		{
			vis[y] = 1;
			if (!mat[y] || match(mat[y]))
			{
				mat[y] = x;
				return 1;
			}
		}
		return 0;
	}

	bool ok()
	{
		REP(i, 1, n) REP(j, 1, n) if (a[i][j] != -1) G[i].emplace_back(j);
		REP(i, 1, n)
		{
			memset(vis, 0, sizeof vis);
			if (!match(i)) return 0;
		}
		return 1;
	}
}

const int N = 4e5;
int prime[N + 5], g[10], p_cnt;
bool notp[N + 5];

inline i64 power_pow(i64 base, int b, const i64 p)
{
    if (!base) return !b;
    i64 ans = 1;
    while (b)
    {
        if (b & 1) (ans *= base) %= p;
        if (b >>= 1) (base *= base) %= p;
    }
    return ans;
}
 
int top, stk[666];
void split(int x)
{
    for (int i = 2; i * i <= x; i++) if (x % i == 0)
    {
        stk[++top] = i;
        while (x % i == 0) x /= i;
    }
    if (x > 1) stk[++top] = x;
}
int calcg(const int p)
{
    split(p - 1);
    REP(i, 1, 114514)
    {
        bool flg = 1;
        REP(j, 1, top) if (power_pow(i, (p - 1) / stk[j], p) == 1) {flg = 0;break;}
        if (flg && power_pow(i, p - 1, p) == 1) return i;
    }
    return -1;
}

int m;

void init()
{
	notp[1] = 1;
	REP(i, 1, N)
	{
		if (!notp[i]) prime[++p_cnt] = i;
		REP(j, 1, p_cnt)
		{
			int t = i * prime[j];
			if (t > N) break;
			notp[t] = 1;
			if (i % prime[j] == 0) break;
		}
	}
	REP(i, 1, p_cnt) if (prime[i] > k && (prime[i] - 1) % k == 0)
		prime[++m] = prime[i];
	srand(time(0));
	random_shuffle(prime + 1, prime + 1 + m);
	m = min(m, 5);
	REP(i, 1, m) g[i] = calcg(prime[i]);
}


namespace fk
{
	int p, g, wk;
	int w[maxn], A[maxn][maxn];
	inline i64 det()
	{
		const int MOD = p;
		i64 ans = 1;
		REP(i, 1, n)
		{
			if (!A[i][i])
			{
				REP(j, i + 1, n) if (A[j][i])
				{
					ans = p - ans;
					REP(k, i, n) swap(A[i][k], A[j][k]);
					break;
				}
			}
			if (!A[i][i]) return 0;
			(ans *= A[i][i]) %= MOD;
			const i64 Inv = power_pow(A[i][i], MOD - 2, MOD);
			REP(j, i + 1, n) if (A[j][i])
			{
				const i64 qaq = Inv * A[j][i] % MOD;
				REP(k, i, n) A[j][k] = (A[j][k] - qaq * A[i][k]) % MOD;
			}
		}
		return (ans + MOD) % MOD;
	}
	int idft(int f[], int s)
	{
		reverse(f + 1, f + k);
		i64 ans = 0;
		const int MOD = p;
		DEP(i, k - 1, 0) ans = (ans * w[s] + f[i]) % MOD;
		i64 ivk = power_pow(k, p - 2, p);
		return ans * ivk % MOD;
	}
	int res[maxn];
	void work()
	{
		const int MOD = p;
		wk = power_pow(g, (MOD - 1) / k, p);
		w[0] = 1;REP(i, 1, k) w[i] = 1ll * w[i - 1] * wk % MOD;
		REP(l, 0, k - 1)
		{
			static int bin[maxn];
			bin[0] = 1;REP(i, 1, k + 5) bin[i] = 1ll * bin[i - 1] * w[l] % MOD;

			REP(i, 1, n) REP(j, 1, n)
				if (a[i][j] != -1) A[i][j] = (rand() % 3 < 10 ? bin[a[i][j]] : MOD - bin[a[i][j]]);
				else A[i][j] = 0;
			res[l] = det();
		}
		if (idft(res, 0))
		{
			puts("Yes");
			exit(0);
		}
	}
	int main()
	{
		init();
		int dfn = 0;
		REP(i, 1, m)
		{
			p = prime[i];g = ::g[i];
			work();
		}
		puts("No");
		return 0;
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output2.txt", "w", stdout);
	cin >> n >> k;
	REP(i, 1, n) REP(j, 1, n) scanf("%d", a[i] + j);
	if (!judge :: ok())
	{
		puts("No");
		return 0;
	}
	if (k == 1) {puts("1");return 0;}
	if (n <= 10) return bf :: main();
	return fk :: main();
	return 0;
}

