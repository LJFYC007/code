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
const int Delta = 1e5;

int T, n;
char s[maxn];
map<int, int> Map[maxn * 2];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d", &n);
		scanf("%s", s + 1);
		REP(i, 0, Delta * 2) Map[i].clear();
		int x = Delta, y = Delta; LL ans = 0;
		++ Map[x][y];
		REP(i, 1, n)
		{
			if ( s[i] == 'U' ) ++ y;
			if ( s[i] == 'D' ) -- y;
			if ( s[i] == 'L' ) -- x;
			if ( s[i] == 'R' ) ++ x;
			ans += Map[x][y];
			++ Map[x][y];
		}
		printf("%lld\n", ans);
	}
    return 0;
}
