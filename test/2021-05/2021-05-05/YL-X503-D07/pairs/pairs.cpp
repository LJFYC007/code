/***************************************************************
	File name: pairs.cpp
	Author: ljfcnyali
	Create time: 2021年05月05日 星期三 09时46分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int T, n;

inline int Solve(int n, int x)
{
	if ( n == 1 ) return 1;
	if ( n < (1 << x) ) return Solve(n, x - 1);
	if ( n < (1 << x) + (1 << x - 1) ) return Solve((1 << x + 1) - n - 1, x - 1) + 1;
	return Solve(n - (1 << x), x - 1);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("pairs.in", "r", stdin);
    freopen("pairs.out", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{ 
		scanf("%d", &n); 
		int x = 1; while ( (1 << x) < n ) ++ x; 
		printf("%d\n", (n - Solve(n, x)) / 2); 
	}
    return 0;
}
