/***************************************************************
	File name: AGC028D.cpp
	Author: ljfcnyali
	Create time: 2021年06月25日 星期五 15时30分46秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 610;
const int Mod = 1e9 + 7;

int n, m, f[maxn][maxn], a[maxn], g[maxn], h[maxn][maxn], ans;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &m);
	g[0] = g[2] = 1; for ( int i = 4; i <= n + n; i += 2 ) g[i] = g[i - 2] * (i - 1) % Mod;
	REP(i, 1, m) { int x, y; scanf("%lld%lld", &x, &y); a[x] = y; a[y] = x; } 
	REP(i, 1, n + n) REP(j, i, n + n) h[i][j] = h[i][j - 1] + (a[j] == 0);
	REP(len, 1, n + n) REP(i, 1, n + n - len + 1)
	{
		int j = i + len - 1, num = 0;
		REP(k, i, j) 
		{
			if ( !a[k] ) { ++ num; continue ; }
			if ( a[k] < i || a[k] > j ) goto Next ;
		}
		f[i][j] = g[num];
		REP(k, i + 1, j - 1) f[i][j] = (f[i][j] - f[i][k] * g[num - h[i][k]]) % Mod;
		ans = (ans + f[i][j] * g[n + n - m - m - num]) % Mod;
Next : ;
	}
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
