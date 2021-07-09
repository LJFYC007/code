/***************************************************************
	File name: AGC034F.cpp
	Author: ljfcnyali
	Create time: 2021年02月22日 星期一 16时33分59秒
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

int n, m, a[maxn], f[maxn], g[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

inline void FWT(int *f, int n, int op)
{
	if ( op == -1 ) op = (Mod + 1) / 2;
	for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
		for ( int i = 0; i < n; i += (Mid << 1) )
			for ( int j = 0; j < Mid; ++ j ) 
			{
				int x = (f[i + j] + f[i + j + Mid]) % Mod; 
				int y = (f[i + j] - f[i + j + Mid]) % Mod; 
				f[i + j] = x * op % Mod; f[i + j + Mid] = y * op % Mod;
			}
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); 
	REP(i, 0, (1 << n) - 1) { scanf("%lld", &a[i]); m += a[i]; } 
	m = power(m, Mod - 2);
	REP(i, 0, (1 << n) - 1) { g[i] = a[i] * m % Mod; f[i] = -1; } 
	f[0] += (1 << n); g[0] -= 1;
	FWT(f, 1 << n, 1); FWT(g, 1 << n, 1);	
	REP(i, 0, (1 << n) - 1) f[i] = f[i] * power(g[i], Mod - 2) % Mod;
	FWT(f, 1 << n, -1);
	REP(i, 1, (1 << n) - 1) f[i] = (f[i] - f[0]) % Mod;
	f[0] = 0;
	REP(i, 0, (1 << n) - 1) printf("%lld\n", (f[i] + Mod) % Mod);
    return 0;
}
