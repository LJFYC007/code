/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年01月16日 星期四 15时20分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 8010;
const int maxm = 2e5 + 10;
const int Mod = 998244353;

int r[maxm];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void NTT(int *f, int n, int inv)
{
	r[0] = 0;
	REP(i, 0, n - 1)
	{
		r[i] = (r[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
		if ( i < r[i] ) swap(f[i], f[r[i]]);
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
				int x = f[i + j], y = f[i + Mid + j] * sum % Mod;
				f[i + j] = (x + y) % Mod; f[i + Mid + j] = (x - y) % Mod;
			}
		}
	}
	if ( inv == -1 )
	{
		inv = power(n, Mod - 2);
		REP(i, 0, n - 1) f[i] = f[i] * inv % Mod;
	}
}

int f[maxn][maxn], n, m, fac[maxn], inv[maxn], ans, a[maxm], b[maxm];

inline int C(int n, int m) { return (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

signed main()
{
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    n = 8009;
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld%lld", &n, &m);
    f[0][0] = 1;
    REP(i, 1, m)
	{
		REP(j, 0, n + 2)
 	   	{
        	f[i][j] = f[i - 1][j] * (1 + j + C(j, 2)) % Mod;
			REP(k, j, j + 2) f[i][j] = (f[i][j] - f[i - 1][k] * C(j + 2, j - k + 2)) % Mod;
    	}
		int k = 1;
        // while ( k <= n + 2 ) k <<= 1; 
		while ( k <= n * 2 + 2 ) k <<= 1;
		REP(j, 0, n + 2) { a[j] = f[i - 1][j] * inv[j] % Mod; b[j] = inv[j]; }
		REP(j, n + 3, k) a[j] = b[j] = 0;
//		REP(j, 0, n + 2) printf("%lld ", a[j]); puts("");
		//REP(j, 0, n + 2) printf("%lld ", b[j]); puts("");
		NTT(a, k, 1); NTT(b, k, 1);
		REP(j, 0, k - 1) a[j] = a[j] * b[j] % Mod;
		NTT(a, k, -1);
//		REP(j, 2, n + 2) printf("%lld ", (a[j] * fac[j] % Mod + Mod) % Mod); puts(""); puts("");
		REP(j, 2, n + 2) f[i][j - 2] = (f[i][j - 2] + a[j] * fac[j]) % Mod;
	//	f[i][0] = 1;
	}
	//REP(i, 1, m) { REP(j, 0, n) printf("%d ", (f[i][j] + Mod) % Mod); puts(""); }
    REP(i, 0, n) ans = (ans + f[m][i] * C(n, i)) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
