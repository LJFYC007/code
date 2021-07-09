#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e5 + 10;

int main()
{
	freopen("library.in", "w", stdout);
	int n = 5000000, m = 1000000;
	srand(time(0));
	printf("%d %d\n", n, n);
	REP(i, 1, n) printf("%d ", rand() % m + 1); puts("");
	REP(i, 1, n) printf("%d ", rand() % m + 1); puts("");
	return 0;
}
