/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年03月21日 星期日 14时57分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

bool vis[210][210];

int main()
{
    freopen("B.in", "w", stdout);
	int n = 200, m = 210, a = 18, b = 21;
	printf("%d %d %d %d\n", n, m, a, b);
	srand(time(0));
	REP(i, 1, m)
	{
		int x = rand() % (n - 1) + 1;
		int y = x + (rand() % 2 == 0 ? a : b);
		while ( vis[x][y] || y > n ) 
		{
			x = rand() % (n - 1) + 1;
			y = x + (rand() % 2 == 0 ? a : b);
		}
		vis[x][y] = true;
		printf("%d %d\n", x, y);
	}
    return 0;
}
