/***************************************************************
	File name: 2.cpp
	Author: ljfcnyali
	Create time: 2019年05月31日 星期五 09时07分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 300010;

int n, m, a[maxn], f[maxn][20], p[maxn], sum, l[maxn], r[maxn], g[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	while ( ~scanf("%d", &n) )
	{
		if ( n == 0 ) return 0;
		scanf("%d", &m);
		REP(i, 1, n) scanf("%d", &a[i]); sum = 0;
		REP(i, 1, n) 
		{
			if ( a[i] == a[i - 1] ) p[i] = p[i - 1] + 1; 
			else 
			{
				p[i] = 1;
				r[sum] = i - 1; l[++ sum] = i;;
			}
			g[i] = sum;
		}
		r[sum] = n;
		REP(i, 1, n) f[i][0] = p[i];
//		REP(i, 1, sum) printf("%d %d %d\n", l[i], r[i], g[i]);
		REP(j, 1, 18)
			REP(i, 1, n)
				f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
//		REP(i ,1, n) printf("%d ", f[i][2]); puts("");
//		REP(i ,1, n) printf("%d ", f[i][1]); puts("");
//		REP(i ,1, n) printf("%d ", f[i][0]); puts("");
		REP(i, 1, m)
		{
			int L, R; scanf("%d%d", &L, &R);
			int ans = 0;
			if ( r[g[L]] >= R ) { printf("%d\n", R - L + 1); continue ; }
			ans = r[g[L]] - L + 1;
			L = r[g[L]] + 1;
	//		printf("%d %d\n", L, R);
			for ( int j = 18; j >= 0; -- j )
			{
				if ( L + (1 << j) - 1 > R ) continue ;
	//			printf("%d %d %d\n", L, j, f[L][j]);

				ans = max(ans, f[L][j]);	
				L += (1 << j);
			}
			printf("%d\n", ans);
		}
	}
    return 0;
}
