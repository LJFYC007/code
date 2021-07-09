/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年02月23日 星期二 15时37分19秒
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
	int n = 1000, m = 500, q = 1000;
	printf("%d %d %d\n", n, m, q);
	REP(i, 1, 500)
		printf("3 %d %d %d\n", 500 + i - 1, 500 + i - 1, 500 + i);
	REP(i, 1, 500)
		printf("2 %d\n", 500 + i);
    return 0;
}
