/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年03月18日 星期四 15时21分52秒
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
	int n = 10; printf("%d %d\n", 10, 10);
	int x = 1; srand(time(0));
	REP(i, 1, n) { x += rand() % 10 + 1; printf("%d ", x); } puts("");
	REP(i, 1, n)
	{
		int l = rand() % n + 1, r = rand() % n + 1;
		if ( l > r ) swap(l, r);
		printf("2 %d %d %d\n", l, r, rand() % 3);
	}
    return 0;
}
