#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 200010;
const int Mod = 998244353;

int r[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void NTT(int *a, int n, int inv)
{
    r[0] = 0; REP(i, 1, n - 1)
    {
        r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
        if ( r[i] > i ) swap(a[i], a[r[i]]);
    }
    for ( int Mid = 1; Mid < n; Mid <<= 1 )
    {
        int tmp = power(3, (Mod - 1) / (Mid << 1));
        if ( inv == -1 ) tmp = power(tmp, Mod - 2);
        for ( int i = 0; i < n; i += (Mid << 1) )
        {
            int sum = 1;
            for ( int j = 0; j < Mid; ++ j, sum = sum * tmp % Mod )
            {
                int x = a[i + j], y = a[i + Mid + j] * sum % Mod;
                a[i + j] = (x + y) % Mod; a[i + Mid + j] = (x - y) % Mod;
            }
        }
    }
    if ( inv == -1 )
    {
        inv = power(n, Mod - 2);
        REP(i, 0, n - 1) a[i] = a[i] * inv % Mod;
    }
}

int f[maxn], n, m, N, ans, fac[maxn], inv[maxn], p[maxn];

inline void Mul(int *a, int *b, int x)
{
	REP(i, 0, m) f[i] = a[i]; REP(i, m + 1, N - 1) f[i] = 0;
	NTT(f, N, 1);
	int sum = 1;
	REP(i, 1, m) { sum = sum * p[x] % Mod; b[i] = b[i] * sum % Mod; }
	NTT(b, N, 1);
	REP(i, 0, N - 1) b[i] = b[i] * f[i] % Mod;
	NTT(b, N, -1);
	REP(i, m + 1, N - 1) b[i] = 0;
}

int a[maxn], b[maxn];

inline int A(int n, int m) { return n < m ? 0 : fac[n] * inv[n - m] % Mod; }

signed main()
{
	freopen("or.in", "r", stdin);
	freopen("or.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	fac[0] = inv[0] = p[0] = 1;
	REP(i, 1,  m) { fac[i] = fac[i - 1] * i % Mod; p[i] = p[i - 1] * 2 % Mod; }
	inv[m] = power(fac[m], Mod - 2); for ( int i = m - 1; i >= 0; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	REP(i, 1, m) a[i] = inv[i]; b[0] = N = 1;
	while ( N < (m << 2) ) N <<= 1;
	for ( int i = 1; i <= n; i <<= 1 )
	{
		if ( n & i ) Mul(a, b, i);
		Mul(a, a, i);
	}
	REP(i, 0, m) ans = (ans + b[i] * A(m, i)) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}
