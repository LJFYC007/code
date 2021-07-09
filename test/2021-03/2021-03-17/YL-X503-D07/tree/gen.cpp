#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e5 + 10;

int main()
{
	freopen("tree.in", "w", stdout);
	int n = 2010; printf("%d\n", n);
	srand(time(0));
	int m = rand() % n + 1;
	REP(i, 2, m) printf("1 ");
	REP(i, m + 1, n) printf("%d ", rand() % m + 1); puts("");
	REP(i, 1, n) printf("%d ", rand() % 1000); puts("");
	return 0;
}
