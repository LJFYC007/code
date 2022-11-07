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
typedef long long LL;

const int maxn = 1e5 + 10;

int main()
{
	freopen("input.txt", "w", stdout);
	int n = 5000, q = 100000;
	printf("%d %d\n", n, q);
	REP(i, 1, q)
	{
		int op = rand() % 2 + 1;
		if ( op == 1 ) 
		{
			int dir = rand() % 4 + 1, x = rand() % n + 1, y = rand() % n + 1;
			int len;
			if ( dir == 1 ) len = rand() % min(n - x, n - y);
			if ( dir == 2 ) len = rand() % min(n - x, y);
			if ( dir == 3 ) len = rand() % min(x, n - y);
			if ( dir == 4 ) len = rand() % min(x, y);
			printf("1 %d %d %d %d\n", dir, x, y, len);
		}
		else printf("2 %d %d\n", rand() % n + 1, rand() % n + 1);
	}
    return 0;
}
