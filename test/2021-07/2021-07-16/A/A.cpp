/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年07月16日 星期五 08时51分03秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e7 + 10;
const int Mod = 1e9 + 7;

int T, n, m, p[maxn], f[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	n = maxn - 10; p[0] = 1; REP(i, 1, n) p[i] = p[i - 1] * 2 % Mod;
	f[0] = 1; REP(i, 1, n) f[i] = f[i - 1] * (p[i] - 1) % Mod;

	scanf("%lld", &T);
	while ( T -- ) 
	{
		scanf("%lld%lld", &n, &m);
		int ans = 1;
		// int ans = f[n] * power(f[n - m], Mod - 2) % Mod;
		// ans = ans * power(2, (m - 1) * m / 2) % Mod;
		ans = ans * f[n] % Mod * power(f[m], Mod - 2) % Mod;
		ans = ans * power(f[n - m], Mod - 2) % Mod;
		printf("%lld\n", (ans + Mod) % Mod);
	}
    return 0;
}
