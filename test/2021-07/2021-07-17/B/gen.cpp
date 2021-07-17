/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年07月17日 星期六 11时28分43秒
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
	int n = 1000000, m = n, q = n; srand(time(0));
	printf("%d %d %d\n", n, m, q);
	REP(i, 1, m)
	{
		int op = rand() % 3 + 1;
		if ( op == 2 ) op = 1;
		if ( op == 1 ) 
			printf("1 %d %d\n", rand() % n + 1, rand() % n + 1);
		if ( op == 2 ) 
		{
			int l = rand() % n + 1, r = rand() % n + 1;
			if ( l > r ) swap(l, r);
			printf("2 %d %d %d\n", l, r, rand() % n + 1);
		}
		if ( op == 3 ) printf("3 %d\n", rand() % n + 1);
	}
	REP(i, 1, q)
	{
		int l = rand() % n + 1, r = rand() % n + 1;
		if ( l > r ) swap(l, r);
		printf("%d %d\n", l, r);
	}
    return 0;
}
