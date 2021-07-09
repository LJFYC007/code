/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年02月26日 星期五 17时13分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int a[5010][5010];

int main()
{
    freopen("input.txt", "w", stdout);
	int n = 50;
	srand(time(0));
	printf("%d\n", n);
	REP(i, 1, n)
	{
		while ( 1)  
		{
			int x = rand() % (n * (n + 1) / 2) + 1;
			REP(j, 1, n) 
			{
				if ( x > 0 && x <= j && !a[j][x] ) { a[j][x] = 1; goto Next ; }
				x -= j;
			}
		}
Next : ;
	}
	REP(i, 1, n) { REP(j, 1, i) printf("%d", a[i][j] ^ 1); puts(""); }
    return 0;
}
