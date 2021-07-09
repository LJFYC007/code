#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5e5 + 10;
const int Mod = 998244353;

int r[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void NTT(int *f, int n, int inv)
{
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
                int x = f[i + j], y = f[i + j + Mid] * sum % Mod;
                f[i + j] = (x + y) % Mod; f[i + j + Mid] = (x - y) % Mod;
            }
        }
    }
    if ( inv == -1 )
    {
        inv = power(n, Mod - 2);
        REP(i, 0, n - 1) f[i] = f[i] * inv % Mod;
    }
}

inline void Inv(int *f, int *g, int n)
{
    if ( n == 1 ) { g[0] = power(f[0], Mod - 2); return ; }
    int len = n + 1 >> 1; Inv(f, g, len);
    int m = 1; while ( m < (n << 1) ) m <<= 1;
    static int a[maxn];
    copy(f, f + n, a); fill(a + n, a + m, 0); fill(g + len, g + m, 0);
    NTT(a, m, 1); NTT(g, m, 1);
    REP(i, 0, m - 1) g[i] = g[i] * ((2 - a[i] * g[i]) % Mod) % Mod;
    NTT(g, m, -1); fill(g + n, g + m, 0);
}

inline void Sqrt(int *f, int *g, int n)
{
    if ( n == 1 ) { g[0] = 1; return ; }
    int len = n + 1 >> 1; Sqrt(f, g, len);
    int m = 1; while ( m < (n << 1) ) m <<= 1;
    static int a[maxn], g0[maxn];
    copy(f, f + n, a); fill(a + n, a + m, 0);
    Inv(g, g0, n);
    NTT(a, m, 1); NTT(g, m, 1); NTT(g0, m, 1);
    REP(i, 0, m - 1) g[i] = (Mod + 1 >> 1) * (g[i] + (a[i] * g0[i] % Mod)) % Mod;
    NTT(g, m, -1); fill(g + n, g + m, 0);
}

inline void ln(int *f, int *g, int n)
{
	int m = 1; while ( m < (n << 1) ) m <<= 1;
	static int a[maxn], b[maxn]; Inv(f, b, n);
	REP(i, 0, n - 2) a[i] = (i + 1) * f[i + 1] % Mod;
	fill(a + n - 1, a + m, 0); fill(b + n, b + m, 0);
	NTT(a, m, 1); NTT(b, m, 1);
	REP(i, 0, m - 1) a[i] = a[i] * b[i] % Mod;
	NTT(a, m, -1);
	g[0] = 0; REP(i, 1, n - 1) g[i] = a[i - 1] * power(i, Mod - 2) % Mod;
}

inline void exp(int *f, int *g, int n)
{
	if ( n == 1 ) { g[0] = 1; return ; }
	int len = n + 1 >> 1; exp(f, g, len);
	int m = 1; while ( m < (n << 1) ) m <<= 1;
	static int a[maxn], b[maxn]; ln(g, b, n); fill(b + n, b + m, 0);
	copy(g, g + len, a); fill(a + len, a + m, 0);
	REP(i, 0, n - 1) b[i] = (f[i] - b[i]) % Mod; ++ b[0];
	NTT(a, m, 1); NTT(b, m, 1);
	REP(i, 0, m - 1) g[i] = a[i] * b[i] % Mod;
	NTT(g, m, -1); fill(g + n, g + m, 0);
}

int F[20][maxn], A[maxn], B[maxn];

inline void Solve(int *f, int l, int r, int d)
{
    if ( l == r ) { f[0] = 1; f[1] = -A[l]; return ; }
    int Mid = l + r >> 1;
    int m = 1; while ( m < (r - l + 1 << 1) ) m <<= 1;
    static int a[maxn], b[maxn];
    Solve(a, l, Mid, d + 1);
    REP(i, 0, Mid - l + 1) F[d + 1][i] = a[i];
    Solve(b, Mid + 1, r, d + 1);
    REP(i, 0, Mid - l + 1) a[i] = F[d + 1][i];
    fill(a + Mid - l + 2, a + m, 0); fill(b + r - Mid + 1, b + m, 0);
    NTT(a, m, 1); NTT(b, m, 1);
    REP(i, 0, m - 1) f[i] = a[i] * b[i] % Mod;
    NTT(f, m, -1); fill(f + r - l + 2, f + m, 0);
}

int n, m, k, a[maxn], b[maxn], fac[maxn], inv[maxn], f[maxn], g[maxn];

signed main()
{
	freopen("shenq.in", "r", stdin);
	freopen("shenq.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	REP(i, 1, n) scanf("%lld", &A[i]);
	REP(i, 1, m) scanf("%lld", &B[i]);
	scanf("%lld", &k);

	if ( k <= 100 )
	{
		a[0] = n; b[0] = m;
		REP(i, 1, k)
		{
			REP(j, 1, n) a[i] = (a[i] + power(A[j], i)) % Mod;
			REP(j, 1, m) b[i] = (b[i] + power(B[j], i)) % Mod;
		}
	}
	else
	{
		int K = max(max(n, m), k);
		Solve(f, 1, K, 1); ln(f, g, K + 1);
  	  	a[0] = n; REP(i, 1, K) a[i] = (-g[i] * i) % Mod;
		mem(f); mem(g); mem(F); mem(A);
		REP(i, 1, m) A[i] = B[i];
		Solve(f, 1, K, 1); ln(f, g, K + 1);
    	b[0] = m; REP(i, 1, K) b[i] = (-g[i] * i) % Mod;
	}

	fac[0] = inv[0] = 1; REP(i, 1, k) fac[i] = fac[i - 1] * i % Mod;
    inv[k] = power(fac[k], Mod - 2); for ( int i = k - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;

	REP(i, 0, k) { a[i] = a[i] * inv[i] % Mod; b[i] = b[i] * inv[i] % Mod; }
	int len = 1; while ( len < (k << 1) ) len <<= 1;
	NTT(a, len, 1); NTT(b, len, 1);
	REP(i, 0, len - 1) a[i] = a[i] * b[i] % Mod;
	NTT(a, len, -1);
	REP(i, 1, k)
	{
		int ans = a[i] * fac[i] % Mod;
		ans = ans * power(n * m % Mod, Mod - 2) % Mod;
		printf("%lld\n", (ans + Mod) % Mod);
	}
	return 0;
}
