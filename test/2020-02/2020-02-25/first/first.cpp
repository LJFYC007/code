#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;

int main()
{
	freopen("first.in", "r", stdin);
	freopen("first.out", "w", stdout);
	int x; scanf("%d", &x);
	int pos = 0;
	REP(i, 1, 500)
	{
		int num = 2 * i + 3;
		int y = i * i + i;
		if ( y > x ) { pos = i - 1; break ; }
	}
	puts("1 2");
	puts("2 3");
	int tot = 3;
	REP(i, 1, pos) { printf("3 %d\n", ++ tot); ++ tot; printf("%d %d\n", tot - 1, tot); }
	int num = pos * pos + pos;
	while ( num < x ) { printf("%d 1\n", ++ tot); ++ num; }
	puts("0 0");
	return 0;
}
