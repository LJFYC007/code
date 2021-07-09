/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年03月14日 星期日 09时33分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 110;
const int N = 1e8;

int n, k, a[maxn][maxn], Mod, g, omega, p[maxn], f[maxn][maxn], h[maxn][maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

inline bool Prime()
{
	for ( int i = 2; i * i <= Mod; ++ i ) 
		if ( Mod % i == 0 ) return false;
	return true;
}

inline bool Check()
{
	int x = Mod - 1;
	for ( int i = 2; i * i <= x; ++ i ) if ( x % i == 0 ) 
	{
		while ( x % i == 0 ) x /= i;
		if ( power(g, (Mod - 1) / i) == 1 ) return false;
	}
	if ( x > 1 && power(g, (Mod - 1) / x) == 1 ) return false;
	return true;
}

inline int Det()
{
	int ret = 1; 
	REP(i, 1, n)
	{
		int pos = -1;
		REP(j, i, n) if ( f[j][i] != 0 ) { pos = j; break ; } 
		if ( pos == -1 ) return 0;
		if ( pos != i ) { REP(j, 1, n) swap(f[pos][j], f[i][j]); ret = -ret; } 
		REP(j, i + 1, n)
		{
			int tmp = power(f[i][i], Mod - 2) * f[j][i] % Mod;
			REP(k, 1, n) f[j][k] = (f[j][k] - f[i][k] * tmp) % Mod;
		}
	}
	REP(i, 1, n) ret = ret * f[i][i] % Mod;
	return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &k);
	REP(i, 1, n) REP(j, 1, n) scanf("%lld", &a[i][j]);
	Mod = N / k * k + 1;
	while ( !Prime() ) Mod -= k;
	g = 3; while ( !Check() ) ++ g;
	omega = power(g, (Mod - 1) / k);
	p[0] = 1; REP(i, 1, k - 1) p[i] = p[i - 1] * omega % Mod;

	REP(i, 1, n) REP(j, 1, n) h[i][j] = rand() % (Mod - 1) + 1;	
	int ans = 0;
	REP(o, 0, k - 1)
	{
		REP(i, 1, n) REP(j, 1, n) 
			if ( a[i][j] == -1 ) f[i][j] = 0;
			else f[i][j] = h[i][j] * power(p[o], a[i][j]) % Mod;
		ans = (ans + Det()) % Mod;
	}
	if ( ans != 0 ) puts("Yes");
	else puts("No");
    return 0;
}
