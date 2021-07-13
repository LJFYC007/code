/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年07月13日 星期二 10时24分31秒
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
	int n = 200000, m = 500000; printf("%d %d\n", n, m);
	REP(i, 1, n) printf("%d ", rand() % 100000 + 1); puts("");
	REP(i, 1, m) 
	{
		int x = rand() % n + 1;
		printf("%d %d\n", x, rand() % ((n - x + 2) / 2));
	}
    return 0;
}
