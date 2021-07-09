#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;

int n;

inline void Solve(int x, int y)
{
	printf("%d %d\n", x, y);
	++ y;
	while ( x <= n - 1 )
	{
		printf("%d %d\n", x, y);
		++ x; -- y;
		printf("%d %d\n", x, y);
		++ x; ++ y;
	}
	printf("%d %d\n", x, y);
	-- y;
	while ( x >= 4 )
	{
		printf("%d %d\n", x, y);
		-- x; ++ y;
		printf("%d %d\n", x, y);
		-- x; -- y;
	}
	printf("%d %d\n", x, y);
	-- x; ++ y; printf("%d %d\n", x, y);
	-- x; ++ y;
}

inline void Solve1(int x, int y)
{
	printf("%d %d\n", x, y);
	++ x;
	while ( y >= 2 )
	{
		printf("%d %d\n", x, y);
		-- x; -- y;
		printf("%d %d\n", x, y);
		++ x; -- y;
	}
	printf("%d %d\n", x, y);
	-- x;
	while ( y <= n - 2 )
	{
		printf("%d %d\n", x, y);
		++ x; ++ y;
		printf("%d %d\n", x, y);
		-- x; ++ y;
	}
	printf("%d %d\n", x, y);
	++ x; ++ y; printf("%d %d\n", x, y);
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	printf("%d\n", n * (n + 1) - 1);
	if ( n & 1 ) for ( int i = 1; i <= n; i += 2 ) Solve(1, i);
	else for ( int i = 1; i <= n; i += 2 ) Solve1(i, n + 1);
	return 0;
}
