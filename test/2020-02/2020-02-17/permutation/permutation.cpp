#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 998244353;

int n, a, b, p[maxn];

namespace Subtask1
{
	int ans;
	bool vis[maxn];

	inline bool Check()
	{
		int sum = 0, Max = 0;
		for ( int i = n; i >= 1; -- i )
			if ( p[i] > Max ) { Max = p[i]; ++ sum; }
		if ( sum == b ) return true;
		return false;
	}

	inline void DFS(int x, int Max, int sum)
	{
		if ( sum > a ) return ;
		if ( sum + (n - x + 1) < a ) return ;
		if ( sum + (n - Max) < a ) return ;
		if ( x == n + 1 )
		{
			if ( Check() ) ++ ans;
			return ;
		}
		REP(i, 1, n)
		{
			if ( vis[i] ) continue ;
			vis[i] = true; p[x] = i;
			DFS(x + 1, max(Max, i), sum + (Max < i ? 1 : 0));
			vis[i] = false;
		}
	}

	int main()
	{
		DFS(1, 0, 0);
		printf("%lld\n", ans);
		return 0;
	}
}

namespace Subtask2
{
	int r[maxn], fac[maxn], inv[maxn];

	inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

	inline void NTT(int *a, int n, int inv)
	{
        vector<unsigned long long> f(n);
        copy(a, a + n, f.begin());
		REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
		REP(i, 0, n - 1) if ( i < r[i] ) swap(f[i], f[r[i]]);
		for ( int Mid = 1; Mid < n; Mid <<= 1 )
		{
			int tmp = power(3, (Mod - 1) / (Mid << 1));
			if ( inv == -1 ) tmp = power(tmp, Mod - 2);
			for ( int i = 0; i < n; i += (Mid << 1) )
			{
				int sum = 1;
				for ( int j = 0; j < Mid; ++ j, sum = sum * tmp % Mod )
				{
                    int x = f[i + Mid + j] * sum % Mod;
					f[i + Mid + j] = f[i + j] - x + Mod;
                    f[i + j] += x;
				}
			}
		}
		if ( inv == -1 )
		{
			inv = power(n, Mod - 2);
			REP(i, 0, n - 1) f[i] = f[i] * inv % Mod;
		}
        REP(i, 0, n - 1) a[i] = f[i] % Mod;
	}

	inline void Mul(int *f, int *g, int *h, int n, int op)
	{
		int len = 1;
        op = op == 1 ? n : (n << 1);
		while ( len < op ) len <<= 1;
		REP(i, n, len - 1) g[i] = h[i] = 0;
		NTT(g, len, 1); NTT(h, len, 1);
		REP(i, 0, len - 1) f[i] = g[i] * h[i] % Mod;
		NTT(f, len, -1);
	}

	inline void Solve(int *f, int n)
	{
		if ( n == 1 ) { f[0] = 0; f[1] = 1; return ; }
		if ( n & 1 )
		{
            int g[n * 4], h[n * 4];
			Solve(g, n - 1);
			REP(i, 2, n) h[i] = 0; h[0] = n - 1; h[1] = 1;
			Mul(f, g, h, n + 1, 0);
			return ;
		}
		int a[n * 4], b[n * 4], g[n * 4], h[n * 4];
		Solve(g, n / 2);
        int N = (n / 2) + 1, x = 1;
		REP(i, 0, N - 1)
		{
			a[i] = fac[N - i - 1] * g[N - i - 1] % Mod;
			b[i] = x * inv[i] % Mod;
			x = x * (n / 2) % Mod;
		}
		Mul(h, a, b, N, 0);
        REP(i, 0, N - 1) if ( i < N - i - 1 ) swap(h[i], h[N - i - 1]);
		REP(i, 0, N - 1) h[i] = h[i] * inv[i] % Mod;
        REP(i, N, n) g[i] = h[i] = 0;
		Mul(f, g, h, n + 1, 1);
	}

	inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

	int main()
	{
		int f[maxn];
		fac[0] = inv[0] = 1; REP(i, 1, n + 10) fac[i] = fac[i - 1] * i % Mod;
		inv[n + 10] = power(fac[n + 10], Mod - 2); for ( int i = n + 9; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
		int N = n - 1, M = a + b - 2;
		int ans = C(a + b - 2, a - 1);
		Solve(f, N);
		ans = ans * f[M] % Mod;
		printf("%lld\n", (ans + Mod) % Mod);
		return 0;
	}
}

signed main()
{
    freopen("permutation.in", "r", stdin);
	freopen("permutation.out", "w", stdout);
	scanf("%lld%lld%lld", &n, &a, &b);
	if ( a == 0 || b == 0 ) { puts("0"); return 0; }
	if ( n == a && a == b && a == 1 ) { puts("1"); return 0; }
	return Subtask2 :: main();
}
