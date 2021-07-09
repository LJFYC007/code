/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年03月14日 星期日 10时36分53秒
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
	int n = 15, k = rand() % 100 + 1; printf("%d %d\n", n,k);
	REP(i, 1, n) 
	{ 
		REP(j, 1, n) 
		{ 
			int x = rand() % (k + k + k); 
			if ( 0 <= x && x < k ) printf("%d ", x); else printf("-1 ");
		}
		puts(""); 
	}
    return 0;
}
