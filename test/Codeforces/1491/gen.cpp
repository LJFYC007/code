/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年03月05日 星期五 14时41分39秒
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
	int n =100000, q = 100000;
	printf("%d %d\n", n, q); srand(time(0));
	REP(i, 2, n) printf("%d ", rand() % (i - 1) + 1); puts("");
	while ( q -- ) 
	{
		int op = rand() % 2;
		if ( op == 0 ) 
		{
			int l = rand() % n + 1, r = rand() % min(n - l + 1, 1000) + 1;
			l = 1; r = n;
			printf("1 %d %d %d\n", l, l + r - 1, rand() % 10);
		}
		else printf("2 %d %d\n", rand() % n + 1, rand() % n + 1);
	}
    return 0;
}
