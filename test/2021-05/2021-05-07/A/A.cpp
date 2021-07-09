/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年05月07日 星期五 09时28分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int maxm = 210;
const int INF = 0x3f3f3f3f;

int T, L, R, f[maxm][maxm][2];

inline int w(int x, int y)
{
	int val = 6;
	REP(i, 1, 5)
	{
		if ( x % 10 == y % 10 ) -- val;
		x /= 10; y /= 10;
	}
	return val;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	REP(len, 2, maxm - 10) REP(i, 1, maxm - 10) REP(k, 0, 1)
	{
		int j = i + len - 1; if ( j > maxm - 10 ) continue ; 
		int x = k == 0 ? i - 1 : j + 1; f[i][j][k] = INF;
		REP(o, i, j) f[i][j][k] = min(f[i][j][k], w(x, o) + max(f[i][o - 1][1], f[o + 1][j][0]));
	}
	while ( T -- ) 
	{
		scanf("%d%d", &L, &R); int ans = INF;
		REP(k, L, R) ans = min(ans, w(k, 0) + max(f[L][k - 1][1], f[k + 1][R][0]));
		printf("%d\n", ans);
	}
    return 0;
}
