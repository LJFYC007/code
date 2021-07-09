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
	int n = 10, m = 3;
	printf("%d %d\n", n, m);
	REP(i, 2, n) printf("%d %d\n", i, rand() % (i - 1) + 1);
	REP(i, 1, n) printf("%d\n", rand() % m + 1);
	return 0;
}
