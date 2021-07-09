/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年04月03日 星期六 10时55分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

bool a[10][10];

int main()
{
    freopen("count.in", "w", stdout);
	srand(time(0));
	int n = rand() % 4 + 2, m = rand() % 4, k = rand() % (n * n);
	printf("%d %d %d\n", n, m, k);
	REP(i, 1, m)
	{
		int x = rand() % n + 1, y = rand() % n + 1;
		while ( a[x][y] ) { x = rand() % n + 1; y = rand() % n + 1; }
		a[x][y] = true; printf("%d %d\n", x, y);
	}
    return 0;
}
