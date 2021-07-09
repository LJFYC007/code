/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年05月07日 星期五 09时11分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, g[21][27]; LL f[1 << 20][27];
char s[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(o, 1, n) 
	{
		scanf("%s", s + 1); int m = str(s + 1);
		REP(x, 0, 26)	
		{
			int lst = x;
			REP(i, 1, m)
			{
				if ( lst == 0 ) { lst = s[i] - 'a' + 1; continue ; }
				if ( lst == s[i] - 'a' + 1 ) lst = 0;
			}
			g[o][x] = lst;
		}
	}
	f[0][0] = 1;
	REP(i, 0, (1 << n) - 1) REP(k, 1, n) if ( !((i >> k - 1) & 1) )	
		REP(j, 0, 26) f[i | (1 << k - 1)][g[k][j]] += f[i][j];
	LL ans = 0; REP(i, 1, 26) ans += f[(1 << n) - 1][i];
	printf("%lld\n", ans);
    return 0;
}
