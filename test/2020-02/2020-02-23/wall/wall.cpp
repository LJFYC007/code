#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

int q, a, b, c, d;

int main()
{
	freopen("wall.in", "r", stdin);
	freopen("wall.out", "w", stdout);
	scanf("%d", &q);
	while ( q -- )
	{
		scanf("%d%d%d%d", &a, &b, &c, &d);
		-- a; -- b; -- c; -- d;
		int ans = 0;
		REP(i, a, c) if ( (i & b) == 0 && (i == a || (i - 1 & b) != 0)  ) ++ ans;
		REP(i, b, d) if ( (i & a) == 0 && (i == b || (i - 1 & a) != 0)  ) ++ ans;
		if ( (a & b) == 0 ) -- ans;
		printf("%d\n", ans);
	}
	return 0;
}
