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

const int maxn = 1e5 + 10;

int T ,n, ans, a[maxn];
bool vis[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- )
	{
		scanf("%d", &n); ans = 0; mem(vis);
		REP(i, 1, n) scanf("%d", &a[i]);
		REP(i, 1, n) REP(j, i + 1, n) if (!vis[a[j] - a[i]] ) { vis[a[j] - a[i]] = true; ++ ans; }
		printf("%d\n", ans);
	}
    return 0;
}
