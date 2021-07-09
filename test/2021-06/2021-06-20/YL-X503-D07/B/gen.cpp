/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年06月20日 星期日 20时34分12秒
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
	int n = 1000, m = 1000; printf("%d %d\n", n, m);
	REP(i, 1, n) printf("%d ", rand() % 1000 + 1); puts("");
	while ( m -- ) 
	{
		int op, l, r; op = rand() % 2 + 1; l = rand() % n + 1; r = rand() % n + 1;
		if ( l > r ) swap(l, r);
		if ( op == 1 ) printf("%d %d %d %d\n", op, l, r, rand() % 10 + 1);
		else printf("%d %d %d\n", op, l, r);
	}
    return 0;
}
