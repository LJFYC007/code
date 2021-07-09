/***************************************************************
	File name: CF1007E.cpp
	Author: ljfcnyali
	Create time: 2021年03月29日 星期一 21时05分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 210;
const int INF = 1e18;

int n, t, k, a[maxn], b[maxn], c[maxn], sa[maxn], sb[maxn], f[maxn][maxn][2], g[maxn][maxn][2];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld", &n, &t, &k);
	REP(i, 1, n) scanf("%lld%lld%lld", &a[i], &b[i], &c[i]);
	++ n; a[n] = c[n] = INF;
	REP(i, 1, n) { sa[i] = sa[i - 1] + a[i]; sb[i] = sb[i - 1] + b[i]; } 
	REP(i, 1, n) REP(j, 0, t) REP(o, 0, 1) f[i][j][o] = g[i][j][o] = INF;
	REP(i, 1, n) REP(j, 0, t) REP(o, 0, 1)
	{
		if ( j * b[i] + o * a[i] <= c[i] && f[i - 1][j][o] != INF ) 
		{
			f[i][j][o] = min(f[i][j][o], f[i - 1][j][o]);
			int x = (sb[i - 1] * j + sa[i - 1] * o + k - 1) / k;
			if ( x * k <= sb[i] * j + sa[i] * o ) g[i][j][o] = min(g[i][j][o], x);
		}
		
		REP(r, 0, j - 1)
		{
			if ( g[i][r][o] == INF ) continue ; 
			int num = sa[i] * o + sb[i] * r - k * g[i][r][o];
			int x = max(0ll, (num + (j - r) * b[i] - c[i] + k - 1) / k);
			if ( k * x > num || f[i - 1][j - r][0] == INF ) continue ; 
			f[i][j][o] = min(f[i][j][o], g[i][r][o] + x + f[i - 1][j - r][0]);
			int y = (sb[i - 1] * (j - r) + k - 1) / k;
			if ( k * y <= (j - r) * sb[i] + num - k * x ) g[i][j][o] = min(g[i][j][o], g[i][r][o] + x + y);
		}
	}
	printf("%lld\n", f[n][t][1]);
    return 0;
}
