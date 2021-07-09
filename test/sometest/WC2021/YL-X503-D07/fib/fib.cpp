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

int n, m;

int main()
{
	freopen("fib.in", "r", stdin);
	freopen("fib.out", "w", stdout);
	scanf("%d%d", &n, &m);
	REP(i, 1, n)
	{
		int a, b; scanf("%d%d", &a, &b);
		if ( !a ) { puts("0"); continue ; }
		if ( !b ) { puts("1"); continue ; }
		int x = (a + b) % m, lst = b, now = 2;
		while ( x )
		{
			int t = lst; lst = x; x = (x + t) % m; ++ now;
			if ( now > m + m ) { puts("-1"); break ; }
		}
		if ( now <= m + m ) printf("%d\n", now);
	}
    return 0;
}
