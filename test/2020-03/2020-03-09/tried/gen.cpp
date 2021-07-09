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
//	freopen("tried.in", "w", stdout);
	srand(time(0));
	int n = 8, m = 7;
	printf("%d %d\n", n, m);
	REP(i, 2, n) printf("%d %d %d\n", i, rand() % (i - 1) + 1, rand() % 10);
	return 0;
}
