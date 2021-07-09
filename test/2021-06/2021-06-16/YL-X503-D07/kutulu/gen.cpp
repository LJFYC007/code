/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年06月16日 星期三 11时46分16秒
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
    freopen("kutulu.in", "w", stdout);
	srand(time(0));
	int n = 1000, k = rand() % n + 1, h = rand() % 10000 + 1;
	printf("%d %d %d\n", n, k, h);
	REP(i, 1, n) printf("%d ", rand() % 2000 + 1); puts("");
	REP(i, 2, n) printf("%d %d\n", i, rand() % (i - 1) + 1);
    return 0;
}
