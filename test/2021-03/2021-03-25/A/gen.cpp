#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e5 + 10;

int main()
{
	freopen("input.txt", "w", stdout);
	srand(time(0));
	int n = 100, m = n, N = 1000000; printf("%d\n", n);
	REP(i, 1, n) printf("%d ", rand() % N + 1); puts("");
	printf("%d\n", n);
	REP(i, 1, n) { int l = rand() % n + 1, r = rand() % n + 1; printf("%d %d\n", min(l, r), max(l, r)); }
	return 0;
}
