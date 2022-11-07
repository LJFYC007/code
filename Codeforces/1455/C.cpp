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

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int T, n, m;
	scanf("%d", &T);
	while ( T -- )
	{
		scanf("%d%d", &n, &m);
		if ( n <= 1 ) { printf("0 %d\n", m); continue ; }
		if ( m >= 1 ) -- n;
		printf("%d %d\n", n, m);
	}
    return 0;
}
