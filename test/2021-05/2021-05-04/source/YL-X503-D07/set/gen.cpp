#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int N = 1e9;
const int maxn = 1e5 + 10;

int main()
{
	freopen("set.in", "w", stdout);
	int n = 50000; printf("%d %d\n", n, n);
	srand(time(0));
	REP(i, 1, n) 
	{
		int l = rand() % N + 1, r = rand() % N + 1;
		printf("%d %d ", min(l, r), max(l, r));
		l = rand() % N + 1; r = rand() % N + 1;
		printf("%d %d\n", min(l, r), max(l, r));
	}
	REP(i, 1, n)
	{
		int l = rand() % n + 1, r = rand() % n + 1;
		printf("%d %d\n", min(l, r), max(l, r));
	}
	return 0;
}
