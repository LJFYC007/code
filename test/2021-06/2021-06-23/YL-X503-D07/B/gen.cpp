/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年06月23日 星期三 20时33分40秒
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
	int n = 50000, m = 50000; printf("%d\n", n);
	REP(i, 1, n) printf("%d ", rand() % 1000000000 + 1); puts("");
	printf("%d\n", m);
	REP(i, 1, m)
	{
		int op = rand() % 3 + 1, l = rand() % (n - 1) + 2, r = rand() % (n - 1) + 2;
		if ( l > r ) swap(l, r);
		if ( op == 1 ) printf("%d %d %d %d\n", op, l, r, rand() % (n - r + l - 1) + 1);
		else printf("%d %d %d\n", op, l, r);
	}
    return 0;
}
