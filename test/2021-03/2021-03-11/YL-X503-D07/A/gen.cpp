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
	int n = 50; printf("%d\n", n);
	srand(time(0));
	REP(i, 1, n) 
	{
		int x = rand() % 70 + 1, y = rand() % 70 + 1;
		printf("%d %d\n", min(x, y), max(x, y));
	}
	return 0;
}
