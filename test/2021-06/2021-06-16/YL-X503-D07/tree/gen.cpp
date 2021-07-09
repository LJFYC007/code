/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年06月16日 星期三 10时07分32秒
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
    freopen("tree.in", "w", stdout);
	srand(time(0));
	int n = 1000, q = 1000; printf("%d %d %d\n", n, q, rand() % 100);
	REP(i, 1, n) printf("%d ", rand() % 1000000000 + 1); puts("");
	while ( q -- ) 
	{
		int op = rand() % 3 + 1, l = rand() % n + 1, r = rand() % n + 1;
		if ( l > r ) swap(l, r);
		if ( op != 2 ) printf("%d %d %d\n", op, l, r);
		else printf("%d %d %d %d\n", op, l, r, rand() % 5000 - 2500);
	}
    return 0;
}
