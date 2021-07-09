/***************************************************************
	File name: AGC035E.cpp
	Author: ljfcnyali
	Create time: 2021年02月14日 星期日 20时45分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 160;

int n, K, Mod, f[maxn][maxn][maxn], ans, g[maxn][maxn];

inline void add(int &x, int y) { x = (x + y) % Mod; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld", &n, &K, &Mod);
	if ( K & 1 ) 
	{
		f[0][0][0] = 1;
		REP(i, 1, n)
		{
			int y = 2 * i, x = y - K;
			REP(j, 0, n) REP(k, 0, n) if ( j <= K + 1 && f[i - 1][j][k] ) 
			{
				add(f[i][0][0], f[i - 1][j][k]); // 都不选
				if ( 1 <= x && x <= n ) 
				{
					if ( j ) add(f[i][j + 1][0], f[i - 1][j][k]); 
					else add(f[i][0][0], f[i - 1][j][k]); // 选左边
				}
				if ( y <= n ) add(f[i][0][k + 1], f[i - 1][j][k]); // 选右边
				if ( 1 <= x && y <= n ) add(f[i][max(j + 1, k + 2)][k + 1], f[i - 1][j][k]); // 选两边
			}
		}
		printf("%lld\n", (f[n][0][0] + Mod) % Mod);
	}
	else
	{
		g[0][0] = 1;				
		REP(i, 1, n) REP(j, 0, K / 2) 
		{
			add(g[i][0], g[i - 1][j]);
			if ( j < K / 2 ) add(g[i][j + 1], g[i - 1][j]);
		}
		int x = n / 2, y = n - x, sum1 = 0, sum2 = 0;
		REP(i, 0, K / 2) add(sum1, g[x][i]);
		REP(i, 0, K / 2) add(sum2, g[y][i]);
		ans = sum1 * sum2 % Mod;
		printf("%lld\n", (ans + Mod) % Mod);
	}
    return 0;
}
