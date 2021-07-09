#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
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

inline void Get1(int *f, int n, int x)
{
    static int a[maxn], b[maxn]; 
    copy(f, f + n, a); 
    REP(o, 2, x)
    {
        copy(a, a + n, b); 
        NTT(f, n, 1); NTT(b, n, 1);
        REP(i, 0, n - 1) f[i] = f[i] * b[i] % Mod;
        NTT(f, n, -1); 
    }
}

inline void Get2(int *f, int n, int x)
{
    static int a[maxn]; copy(f, f + n, a); fill(f, f + n, 0);
    REP(i, 0, n - 1)
    {
        if ( x * i >= n ) break ; 
        f[x * i] = a[i];
    }
}

inline void Solve(int *f, int n)
{
    if ( n == 1 ) { f[0] = 1; return ; }
    int len = n >> 1; Solve(f, len); 
    int m = n * 2;

    static int a[maxn], b[maxn], A[maxn], B[maxn]; 
    copy(f, f + len, a); fill(a + len, a + m, 0); Get1(a, m, 3);
    copy(f, f + len, b); fill(b + len, b + m, 0); Get2(b, m, 3);
    REP(i, 1, n - 1) A[i] = 2 * (a[i - 1] - b[i - 1]) % Mod; A[0] = -6;
    copy(f, f + len, a); fill(a + len, a + m, 0); Get1(a, m, 2);
    copy(f, f + len, b); fill(b + len, b + m, 0); Get2(b, m, 2);
    REP(i, 1, n - 1) B[i] = 3 * (a[i - 1] + b[i - 1]) % Mod; B[0] = -6;

    copy(B, B + n, a); Inv(a, B, n); fill(B + n, B + m, 0);
    /*
    printf("%lld\n", n);
    REP(i, 0, n - 1) printf("%lld ", (A[i] + Mod) % Mod); puts("");
    REP(i, 0, n - 1) printf("%lld ", (B[i] + Mod) % Mod); puts("");
    */
    NTT(A, m, 1); NTT(B, m, 1);
    REP(i, 0, m - 1) f[i] = A[i] * B[i] % Mod;
    NTT(f, m, -1); fill(f + n, f + m, 0);

    /*REP(i, 0, n - 1) printf("%lld ", (f[i] + Mod) % Mod); puts("");
    puts("");
    */
}

int n, f[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    int m = 1; while ( m < (n << 1) ) m <<= 1;
    Solve(f, m);
    printf("%lld\n", (f[n] + Mod) % Mod);
    return 0;
}
