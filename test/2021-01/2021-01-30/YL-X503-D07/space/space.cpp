/***************************************************************
	File name: space.cpp
	Author: ljfcnyali
	Create time: 2021年01月30日 星期六 10时58分01秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5010;
const int Mod = 998244353;

int N, q, a[maxn], f[maxn][maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int calc(int n) { return (n * (n - 1) * (n - 2) / 6) % Mod; }

signed main()
{
    freopen("space.in", "r", stdin);
    freopen("space.out", "w", stdout);
	scanf("%lld%lld", &N, &q);
	REP(i, 1, N) scanf("%lld", &a[i]);
	REP(i, 1, N) 
	{
		f[i][i] = 1;
		REP(j, i + 1, N) 
		{
			int x = 2 * i * (j - i - 1) % Mod * power(calc(j), Mod - 2) % Mod;
			REP(k, 1, N) f[j][k] = (f[j][k] + f[i][k] * x) % Mod;
		}
	}
	while ( q -- ) 
	{
		int op; scanf("%lld", &op);
		if ( op == 0 ) { int l, r, x; scanf("%lld%lld%lld", &l, &r, &x); REP(i, l, r) a[i] = (a[i] + x) % Mod; }
		else 
		{
			int n, m; scanf("%lld%lld", &n, &m); int ans = 0;
			REP(i, m + 1, n) ans = (ans + f[n][i] * a[i]) % Mod;
			printf("%lld\n", (ans + Mod) % Mod);
		}
	}
    return 0;
}
