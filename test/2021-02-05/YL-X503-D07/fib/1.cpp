/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, f[maxn];

inline int exgcd(int a, int b, int &x, int &y)
{
	if ( !b ) { x = 1; y = 0; return a; }
	int d = exgcd(b, a % b, x, y);
	int t = x; x = y; y = t - a / b * y;
	return d;
}

inline int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }

int main()
{
	freopen("fib.in", "r", stdin);
	freopen("fib.out", "w", stdout);
	n = maxn - 10; f[3] = 1;
	scanf("%d%d", &n, &m);
	while ( n -- )
	{
		int a, b, x, y; scanf("%d%d", &a, &b);
		if ( !a ) { puts("0"); continue ; }
		if ( !b ) { puts("1"); continue ; }
		int d = exgcd(a, b, x, y), B = a + b;
		int A = abs((y - x) * m);
	}
    return 0;
}
