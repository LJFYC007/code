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

int T, u, v, n, a[maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d%d%d", &n, &u, &v);
		REP(i, 1, n) scanf("%d", &a[i]);
		int Max = 0; REP(i, 1, n - 1) Max = max(Max, abs(a[i] - a[i + 1]));
		if ( Max >= 2 ) puts("0");
		else if ( Max == 1 ) printf("%d\n", min(u, v));
		else printf("%d\n", min(u + v, v + v));
	}
    return 0;
}
