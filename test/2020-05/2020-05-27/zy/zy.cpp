#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 110;
const int Mod = 1004535809;

int f[maxn][maxn][maxn], n, a[maxn], fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; };

signed main()
{
    freopen("zy.in", "r", stdin);
	freopen("zy.out", "w", stdout);
	scanf("%lld", &n);
	fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	REP(i, 1, n) scanf("%lld", &a[i]);
    f[0][0][0] = 1;
	REP(i, 1, n) REP(j, 0, n) REP(t, 0, n)
    {
        f[i][j][t] = f[i - 1][j][t];
		REP(k, 0, min(a[i] - 1, j))
			if ( t ) f[i][j][t] = (f[i][j][t] + f[i - 1][j - k][t - 1] * inv[k]) % Mod;
    }
	REP(i, 1, n)
	{
		if ( i == 1 ) { printf("%lld ", n); continue ; }
		printf("%lld ", f[n][i - 2][i] * fac[i - 2] % Mod);
	}
	puts("");
	return 0;
}
