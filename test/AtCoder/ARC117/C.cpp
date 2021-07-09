/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年04月18日 星期日 20时08分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 4e5 + 10;

int n, ans, f[maxn], g[maxn];
char s[maxn];

inline int C(int n, int m)
{
	if ( f[n] - f[m] - f[n - m] > 0 ) return 0;
	return g[n] * g[m] * g[n - m] % 3; 
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); scanf("%s", s + 1);
	g[0] = 1; 
	REP(i, 1, n) 
	{
		f[i] = f[i - 1]; 
		int x = i; while ( x % 3 == 0 ) { ++ f[i]; x /= 3; } 
		g[i] = g[i - 1] * x % 3;
	}
	REP(i, 1, n)
	{
		int c = 0; if ( s[i] == 'W' ) c = 1; if ( s[i] == 'R' ) c = 2;
		ans = (ans + c * C(n - 1, i - 1)) % 3;
	}
	if ( ((n - 1) & 1) && ans ) ans = 3 - ans;
	if ( ans == 0 ) puts("B");
	if ( ans == 1 ) puts("W");
	if ( ans == 2 ) puts("R");
    return 0;
}
