/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年03月25日 星期四 16时41分18秒
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
	srand(time(0));
	int n = 500000, m = n - 1, k = 4; printf("%d %d %d\n", n, m, k);
	REP(i, 1, n) printf("%d ", rand() % k + 1); puts("");
	REP(i, 1, n) printf("%d ", rand() % 100 + 1); puts("");
	REP(i, 2, n) printf("%d %d\n", i, rand() % (i - 1) + 1);
	REP(i, n, m)
	{
		int x = rand() % n + 1, y = rand() % n + 1;
		while ( x == y ) x = rand() % n + 1;
		printf("%d %d\n", x, y);
	}
	puts("0");
    return 0;
}
