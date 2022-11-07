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
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;

inline int Rand()
{
	int x = rand();
	x = x ^ (rand() << 10);
	x = x ^ (rand() << 20);
	return abs(x);
}

signed main()
{
	freopen("sequence1.in", "w", stdout);
	srand(time(0));
	int n = 10, m = 1000000000;
	printf("%lld\n", n);
	REP(i, 1, n) printf("%lld ", Rand() % (m + m) - m);
	puts("");
    return 0;
}
