/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年03月25日 星期四 21时58分54秒
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

int n, m, a[maxn], Next[maxn], pre[maxn], b[maxn], ans, fac[maxn], inv[maxn];
bool vis[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &m); fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	REP(i, 1, m) { scanf("%lld", &a[i]); pre[i] = b[a[i]]; b[a[i]] = i; } 
	int j = 0;
	REP(i, 2, m)
	{
		while ( j && j + 1 - pre[j + 1] != i - max(i - j - 1, pre[i]) ) j = Next[j];
		if ( j + 1 - pre[j + 1] == i - max(i - j - 1, pre[i]) ) ++ j;
		Next[i] = j;
	} 
	int i = m, num = 0;
	while ( i ) { vis[i] = true; i = Next[i]; }
	REP(i, 1, m)
	{
		if ( !pre[i] ) ++ num;		
		if ( !vis[i] ) continue ;
		ans = (ans + power(n, i) * fac[n - num]) % Mod;
	}
	ans = ans * inv[n] % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
