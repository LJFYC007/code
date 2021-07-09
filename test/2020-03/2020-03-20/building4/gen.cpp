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
	freopen("input.txt", "w", stdout);
	srand(time(0));
	int n = 10;
	printf("%d\n", n);
	int now = 0;
	REP(i, 1, n * 2)
	{
		now += rand() % 10 + 1;
		now -= rand() % 3;
		printf("%d ", now);
	}
	puts("");
	now = 0;
	REP(i, 1, n * 2)
	{
		now += rand() % 10 + 1;
		now -= rand() % 3;
		printf("%d ", now);
	}
	puts("");
	return 0;
}
