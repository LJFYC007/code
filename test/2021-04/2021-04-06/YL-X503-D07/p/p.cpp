/***************************************************************
	File name: p.cpp
	Author: ljfcnyali
	Create time: 2021年04月06日 星期二 09时23分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 998244353;

int T, n, m, a[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("p.in", "r", stdin);
    freopen("p.out", "w", stdout);
#endif
	scanf("%lld", &T);
	while ( T -- ) 
	{
		scanf("%lld%lld", &n, &m);
		if ( n <= m ) { puts("2"); continue ; } 
		if ( m == 1 ) 
		{
			int ans = (1 + 3 * n) % Mod;
			ans = ans * power(2, Mod - 2) % Mod;
			printf("%lld\n", (ans + Mod) % Mod);
			continue ; 
		}
		int A = n + n - m, B = n + n;
		REP(i, 1, n) 
		{
			a[i] = A * power(B, Mod - 2) % Mod;
			if ( A >= n + m ) { B = A; A = A - m; }
			else
			{
				B = A * 2;
				A = B - m - (A - n);
			}
		}
		int x = 1, y = a[n];
		for ( int i = n - 1; i >= 1; -- i ) 
		{
			x = (1 + x * a[i]) % Mod;
			y = y * a[i] % Mod;
		}
		int ans = x * power(1 - y, Mod - 2) % Mod;
		printf("%lld\n", (ans + Mod) % Mod);
	}
    return 0;
}
