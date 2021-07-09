/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年04月02日 星期五 10时50分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int a[maxn];

int main()
{
    freopen("tearssp.in", "w", stdout);
	/*
	int n = 100000, m = 200, root = 1;
	printf("%d %d %d\n", n, m, root); srand(time(0));
	REP(i, 2, n) printf("%d %d %d\n", rand() % (i - 1) + 1, i, rand());
	REP(i, 1, n) printf("%d ", rand() % n + 1);
	REP(i, 1, m)
	{
		int op = rand() % 2 + 1;
		int l =  rand() % n + 1, r = rand() % n + 1;
		if ( l > r ) swap(l, r);
		printf("%d %d %d\n", op, l, r);
	}
	*/

	int n = 20000, m = 20000, root = 1;
	printf("%d %d %d\n", n, m, root); srand(time(0));
	int b = sqrt(n), k = 0;
	for ( int l = 2, r = b + 1; l <= n; l += b, r = min(n, r + b) )
	{
		printf("%d %d %d\n", 1, l, rand());
		REP(i, l + 1, r) printf("%d %d %d\n", i, i - 1, rand());
		a[++ k] = r;
	}
	REP(i, 1, n) printf("%d ", a[rand() % k + 1]);
	REP(i, 1, m)
	{
		int op = rand() % 10 + 1;
		if ( op != 1 )  op = 2;
		int l =  rand() % n + 1, r = rand() % n + 1;
		if ( l > r ) swap(l, r);
		printf("%d %d %d\n", op, l, r);
	}
    return 0;
}
