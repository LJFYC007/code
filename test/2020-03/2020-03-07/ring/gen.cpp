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
	freopen("ring.in", "w", stdout);
	int n = 100, m = 51; printf("%d %d\n", n, m);
	REP(i, 1, n) printf("%d ", rand() % 100 + 1); puts("");
	REP(i, 0, n / 2) printf("%d\n", i);
	return 0;
}
