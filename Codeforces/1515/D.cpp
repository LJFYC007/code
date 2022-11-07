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

const int maxn = 2e5 + 10;

int T, n, l, r, a[maxn], b[maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d%d%d", &n, &l, &r);
		REP(i, 1, n) a[i] = b[i] = 0;
		REP(i, 1, l) { int x; scanf("%d", &x); ++ a[x]; }
		REP(i, 1, r) { int x; scanf("%d", &x); ++ b[x]; } 
		int ans = 0, sum1 = 0, sum2 = 0;
		REP(i, 1, n) { int val = min(a[i], b[i]); a[i] -= val; b[i] -= val; } 
		int j = 1;
		REP(i, 1, n) if ( a[i] & 1 ) 
		{
			while ( j <= n )
			{
				if ( b[j] & 1 ) { -- a[i]; -- b[j]; ++ ans; break ; }
				++ j;
			}
		}	
		j = 1;
		REP(i, 1, n) if ( a[i] & 1 ) 
		{
			while ( j <= n )
			{
				if ( b[j] > 0 ) { -- a[i]; -- b[j]; ++ ans; break ; }
				++ j;
			}
		}
		j = 1;
		REP(i, 1, n) if ( b[i] & 1 ) 
		{
			while ( j <= n )
			{
				if ( a[j] & 1 ) { -- b[i]; -- a[j]; ++ ans; break ; }
				++ j;
			}
		}	
		j = 1;
		REP(i, 1, n) if ( b[i] & 1 ) 
		{
			while ( j <= n )
			{
				if ( a[j] > 0 ) { -- b[i]; -- a[j]; ++ ans; break ; }
				++ j;
			}
		}
		REP(i, 1, n) ans += a[i] / 2 + b[i] / 2 + a[i] % 2 + b[i] % 2;
		printf("%d\n", ans);
	}
    return 0;
}
