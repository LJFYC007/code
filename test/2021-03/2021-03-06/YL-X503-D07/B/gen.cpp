#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e5 + 10;

int main()
{
	freopen("B.in", "w", stdout);
	int n = 300; printf("%d 0\n", n); srand(time(0));
	REP(i, 1, n) printf("%d ", rand() % 100); puts("");
	REP(i, 2, n) printf("%d %d %d\n", rand() % (i - 1) + 1, rand() % 100, rand() % 100);
	return 0;
}
