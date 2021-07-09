/***************************************************************
	File name: AGC030F.cpp
	Author: ljfcnyali
	Create time: 2021年04月01日 星期四 11时27分01秒
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

int n, f[maxn][maxn][maxn], a[maxn], p[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n + n) { scanf("%lld", &a[i]); if ( a[i] != -1 ) p[a[i]] = i; } 
	int num = 0; REP(i, 1, n) if ( a[i + i] == -1 && a[i + i - 1] == -1 ) ++ num;
	f[0][num][0] = 1; int t = 0;
	REP(i, 1, n + n) 
	{
		REP(j, 0, n) REP(k, 0, n + n) if ( f[i - 1][j][k] ) 
		{
			if ( p[i] )
			{
				int x = p[i], y = x & 1 ? x + 1 : x - 1;
				if ( a[y] != -1 ) f[i][j][k] = (f[i][j][k] + f[i - 1][j][k]); 
				else
				{
					if ( k > 0 ) f[i][j][k - 1] = (f[i][j][k - 1] + f[i - 1][j][k] * k) % Mod;
					f[i][j][k] = (f[i][j][k] + f[i - 1][j][k]) % Mod;
				}
			}
			else
			{
				if ( j > 0 ) f[i][j - 1][k] = (f[i][j - 1][k] + f[i - 1][j][k] * j) % Mod;
				f[i][j][k + 1] = (f[i][j][k + 1] + f[i - 1][j][k]) % Mod;
				if ( t + 2 * (num - j) + k > 0 ) f[i][j][k] = (f[i][j][k] + f[i - 1][j][k]) % Mod;
			}
		}
		if ( p[i] )
		{
			int x = p[i], y = x & 1 ? x + 1 : x - 1;
			if ( a[y] == -1 ) ++ t;
		}
		else -- t;
	}
	printf("%lld\n", f[n + n][0][0]);
    return 0;
}
