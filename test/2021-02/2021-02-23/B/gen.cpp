/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年02月23日 星期二 21时32分51秒
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
	int n = 1000000, m = n - 1, q = 1000000;
	printf("%d %d %d\n", n, m, q);
	REP(i, 2, n) printf("%d %d\n", i, rand() % (i - 1) + 1);
	REP(i, 1, q)
	{
		int op = rand() % 2 + 1;
		if ( op == 1 ) printf("1 %d\n", rand() % n + 1);
		else printf("2 %d %d\n", rand() % n + 1, rand() % n + 1);
	}
    return 0;
}
