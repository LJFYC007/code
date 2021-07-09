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
	srand(time(0));
	int n = 5, m = 5;
	printf("%d %d\n", n, m);
	REP(i, 2, n) printf("%d %d\n", rand() % (i - 1) + 1, i);
	REP(i, 1, m)
	{
		int u = rand() % n + 1, v = rand() % n + 1;
		while ( u == v ) v = rand() % n + 1;
		printf("%d %d %d\n", u, v, rand() % 5);
	}
	return 0;
}
