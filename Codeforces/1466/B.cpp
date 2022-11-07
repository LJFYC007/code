/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3e5 + 10;

int T, n, a[maxn], ans, b[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- )
	{
		scanf("%d", &n); ans = 0; REP(i, 0, n + n + n) a[i] = b[i] = 0;
		REP(i, 1, n) { int x; scanf("%d", &x); ++ a[x]; }
		REP(i, 1, n + n + n)
		{
			if ( b[i] ) { b[i + 1] += a[i]; a[i] = 0; }
			else if ( a[i] > 1 ) { b[i + 1] += a[i] - 1; a[i] = 1; }
		}
		REP(i, 1, n + n + n) if ( a[i] + b[i] ) ++ ans;
		printf("%d\n", ans);
	}
    return 0;
}
