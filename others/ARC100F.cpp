/***************************************************************
	File name: ARC100F.cpp
	Author: ljfcnyali
	Create time: 2021年06月15日 星期二 16时31分52秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2.5e4 + 10;
const int maxm = 410;
const int Mod = 1e9 + 7;

int n, m, k, a[maxn], f[maxn][maxm], ans, fac[maxn];
bool vis[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld", &n, &k, &m); REP(i, 1, m) scanf("%lld", &a[i]);
	fac[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;

	REP(i, 1, m - k + 1) 
	{
		REP(j, i, i + k - 1) vis[a[j]] = true;
		bool flag = true; REP(j, 1, k) if ( !vis[j] ) flag = false;
		if ( flag ) { printf("%lld\n", power(k, n - m) * (n - m + 1) % Mod); return 0; } 
		REP(j, i, i + k - 1) vis[a[j]] = false;
	}
	
	REP(i, 1, k - 1) f[0][i] = 1;
	REP(i, 1, n) 
	{
		int sum = 0;
		REP(j, 1, k - 1) 
		{
			sum = (sum + f[i - 1][j]) % Mod;
			f[i][j] = (sum + f[i - 1][j + 1] * (k - j)) % Mod; 
		}
	}

	int pre = 0, suf = 0;
	while ( pre < m && !vis[a[pre + 1]] ) vis[a[++ pre]] = true;
	mem(vis); while ( suf < m && !vis[a[m - suf]] ) { vis[a[m - suf]] = true; ++ suf; }

	int sum = power(k, n - m);
	REP(i, 1, n - m + 1)
	{
		int x = i - 1, y = n - i - m + 1, num = sum - f[x][pre] * f[y][suf];
		if ( pre == m ) REP(j, 1, x)
		{
			if ( j + m >= k ) break ;
			if ( y >= k - j - m ) num = (num + fac[k - m] * f[x - j][k - 1] % Mod * f[y - (k - j - m)][k - j]) % Mod;
		}
		ans = (ans + num) % Mod;
	}
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
