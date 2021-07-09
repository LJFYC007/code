/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年06月30日 星期三 10时11分20秒
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
    freopen("interval.in", "w", stdout);
	srand(time(0));
	int n = 500000; printf("%d %d %d\n", n, n, n);
	REP(i, 1, n) printf("%d ", rand() % 3 + 1); puts("");
	REP(i, 1, n)
	{
		int l = rand() % n + 1, r = rand() % n + 1;
		printf("%d %d\n", min(l, r), max(l, r));
	}
    return 0;
}
