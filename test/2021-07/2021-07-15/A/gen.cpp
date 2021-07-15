/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年07月15日 星期四 16时03分11秒
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
	int T = 1; printf("%d\n", T);
	while ( T -- )
	{
		int m = 5000, n = 5000; printf("%d %d\n", m, n);
		REP(i, 1, n) printf("%d %d\n", rand() % m + 1, rand() % m + 1);	
		printf("%d\n", n);
		REP(i, 1, n) printf("%d %d\n", rand() % m + 1, rand() % m + 1);	
	}
    return 0;
}
