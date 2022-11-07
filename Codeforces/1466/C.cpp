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
const int INF = 0x3f3f3f3f;

int T, n, ans;
char s[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- )
	{
		scanf("%s", s + 1); n = str(s + 1); ans = 0;
		REP(i, 2, n)
			if ( s[i] == s[i - 1] || s[i] == s[i - 2] ) { s[i] = 'A'; ++ ans; }
		printf("%d\n", ans);
	}
    return 0;
}
