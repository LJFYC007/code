/***************************************************************
	File name: AGC028F.cpp
	Author: ljfcnyali
	Create time: 2021年06月29日 星期二 14时39分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1510;

int n, a[maxn][maxn], s[maxn][maxn], l[2][maxn][maxn], r[2][maxn][maxn];
pii pre[maxn][maxn]; vector<pii> f[maxn][maxn]; LL ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) 
	{ 
		getchar(); 
		REP(j, 1, n) { char c = getchar(); if ( c != '#' ) a[i][j] = c - '0'; }
	}
	REP(i, 1, n) REP(j, 1, n) s[i][j] = s[i][j - 1] + a[i][j];
	REP(i, 1, n) REP(j, 1, n) if ( a[i][j] ) 
	{
		pre[i][j] = pii(i, j);
		if ( a[i - 1][j] && pre[i - 1][j] < pre[i][j] ) pre[i][j] = pre[i - 1][j];
		if ( a[i][j - 1] && pre[i][j - 1] < pre[i][j] ) pre[i][j] = pre[i][j - 1];
		f[pre[i][j].first][pre[i][j].second].push_back(pii(i, j));
	}

	int op = 0; REP(j, 1, n + 1) REP(k, 1, n) l[op][j][k] = n + 1;
	for ( int i = n; i >= 1; -- i ) 
	{
		REP(j, 1, n + 1) REP(k, 1, n) l[op ^ 1][j][k] = n + 1, r[op ^ 1][j][k] = 0;
		for ( int j = n; j >= 1; -- j ) if ( a[i][j] )
		{
			l[op ^ 1][j][i] = r[op ^ 1][j][i] = j; 
			REP(k, i, n)
			{
				l[op ^ 1][j][k] = min(l[op ^ 1][j][k], min(l[op][j][k], l[op ^ 1][j + 1][k]));
				r[op ^ 1][j][k] = max(r[op ^ 1][j][k], max(r[op][j][k], r[op ^ 1][j + 1][k]));
			}
		}
		op ^= 1;

		for ( int j = n; j >= 1; -- j ) if ( a[i][j] ) 
		{
			int ret = 0;
			REP(k, i, n) if ( r[op][j][k] >= l[op][j][k] ) ret += s[k][r[op][j][k]] - s[k][l[op][j][k] - 1];
			ans += (ret - a[i][j]) * a[i][j];
			for ( auto it : f[i][j] ) 
				REP(i, it.second, n) s[it.first][i] -= a[it.first][it.second];
		}
	}
	printf("%lld\n", ans);
    return 0;
}
