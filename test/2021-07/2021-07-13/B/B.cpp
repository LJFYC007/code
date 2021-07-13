/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年07月13日 星期二 09时45分41秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 1e18;
const int maxm = 62000000;

int n, B, q, a[maxn], *ans[573][2], f[510][510][2][2], g[2][maxn][176];
int belong[maxn], m, ret, len[maxn]; pii p[maxn]; int A[maxm];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &q); B = 350;
	REP(i, 1, n) scanf("%lld", &a[i]);
	for ( int l = 1, r = min(n, B); l <= n; l += B, r = min(r + B, n) )
	{
		p[++ m] = pii(l, r); 
		REP(i, l, r) belong[i] = m;
	}
	int *now = A; p[m + 1].first = n + 1;
	REP(i, 1, m + 1) REP(o, 0, 1) 
	{
		len[i] = (n - p[i].first + 2) / 2 + 10;
		ans[i][o] = now; now += len[i];
		REP(j, 0, len[i] - 1) ans[i][o][j] = -INF;
	}
	ans[m + 1][0][0] = 0;

	for ( int i = m; i >= 1; -- i ) 
	{
		int l = p[i].first, r = p[i].second;
		REP(i, l, r) REP(j, 0, B / 2) REP(x, 0, 1) REP(y, 0, 1) f[i - l + 1][j][x][y] = -INF;
		f[r - l + 1][0][0][0] = 0; f[r - l + 1][1][1][1] = a[r];
		for ( int i = r - 1; i >= l; -- i ) REP(j, 0, B / 2) REP(y, 0, 1)
		{
			f[i - l + 1][j][0][y] = max(f[i + 1 - l + 1][j][0][y], f[i + 1 - l + 1][j][1][y]);
			if ( j >= 1 ) f[i - l + 1][j][1][y] = f[i + 1 - l + 1][j - 1][0][y] + a[i];
		}
		REP(i, l, r) REP(j, 0, B / 2) REP(y, 0, 1) g[y][i][j] = max(f[i - l + 1][j][0][y], f[i - l + 1][j][1][y]);

		REP(o, 0, 1) REP(x, 0, 1) REP(y, 0, 1) if ( x != 1 || y != 1 ) 
		{
			int posl = 0, posr = 0;	
			REP(j, 0, len[i] - 1)
			{
				ans[i][o][j] = max(ans[i][o][j], f[1][posl][o][x] + ans[i + 1][y][posr]);
				if ( posl < B / 2 && f[1][posl + 1][o][x] - f[1][posl][o][x] > ans[i + 1][y][posr + 1] - ans[i + 1][y][posr] )
					++ posl;
				else if ( posr + 1 < len[i + 1] ) ++ posr;
			}
		}
	}

	while ( q -- ) 
	{
		int i, c; scanf("%lld%lld", &i, &c);	
		i = (i + ret) % n + 1; c = (c + ret) % n + 1;
		ret = 0;
		REP(x, 0, 1) REP(y, 0, 1) if ( x != 1 || y != 1 ) 
			REP(j, 0, min(B / 2, c)) if ( c - j < len[belong[i] + 1] ) 
				ret = max(ret, g[x][i][j] + ans[belong[i] + 1][y][c - j]);
		printf("%lld\n", ret);
	}
    return 0;
}
