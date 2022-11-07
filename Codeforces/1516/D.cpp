/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, q, a[maxn], f[maxn][20], g[maxn], prime[maxn], tot, p[maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	n = maxn - 10; 
	REP(i, 2, n)
	{
		if ( !p[i] ) { p[i] = i; prime[++ tot] = i; } 
		for ( int j = 1; j <= tot && i * prime[j] <= n; ++ j ) 
		{
			p[i * prime[j]] = prime[j];
			if ( i % prime[j] == 0 ) break ; 
		}
	}

	scanf("%d%d", &n, &q); REP(i, 1, n) scanf("%d", &a[i]); 
	REP(i, 1, n + 1) REP(j, 0, 20) f[i][j] = n;
	REP(i, 1, maxn - 10) g[i] = n + 1;
	for ( int i = n; i >= 1; -- i ) 
	{
		int x = a[i]; while ( x > 1 ) { f[i][0] = min(f[i][0], g[p[x]] - 1); x /= p[x]; }
		f[i][0] = min(f[i][0], f[i + 1][0]);
		x = a[i]; while ( x > 1 ) { g[p[x]] = i; x /= p[x]; }
	}
	REP(j, 1, 18) REP(i, 1, n) f[i][j] = f[f[i][j - 1] + 1][j - 1];


	REP(i, 1, q)
	{
		int l, r; scanf("%d%d", &l, &r); int ans = 1;
		for ( int j = 18; j >= 0; -- j ) if ( f[l][j] < r ) 
		{
			ans += (1 << j);
			l = f[l][j] + 1;
		}
		printf("%d\n", ans);
	}
    return 0;
}
