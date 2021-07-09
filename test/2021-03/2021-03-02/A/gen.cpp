#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e5 + 10;

bool a[100][100];

int main()
{
	freopen("input.txt", "w", stdout);
	srand(time(0));
	int n = 10, m = n - 1 + rand() % 3; printf("%d %d\n", n, m);
	REP(i, 2, n) 
	{
		int x = i, y = rand() % (i - 1) + 1;
		a[x][y] = a[y][x] = true; printf("%d %d\n", x, y);
	}
	REP(i, n, m) 
	{
		int x = rand() % n + 1, y = rand() % n + 1;
		while ( a[x][y] || x == y ) 
		{
			x = rand() % n + 1; y = rand() % n + 1;
		}
		a[x][y] = a[y][x] = true; printf("%d %d\n", x, y);
	}
	return 0;
}
