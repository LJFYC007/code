/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2021年03月16日 星期二 21时35分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1010;
const int Mod = 998244353;

int n, m, x, y, ans, fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int C(int n, int m) { return n < m ? 0 : fac[n] * inv[m] % Mod * inv[n - m] % Mod; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	cin >> n >> m; int x1, x2, y1, y2; cin >> x1 >> y1 >> x2 >> y2;
	if ( x1 > x2 ) swap(x1, x2); if ( y1 > y2 ) swap(y1, y2);
	int A = x1 - 1, B = n - x2, C = y1 - 1, D = m - y2, E = x2 - x1 + y2 - y1;
	REP(i, 1, A) ans = (ans + power(E + i, Mod - 2)) % Mod;
	REP(i, 1, B) ans = (ans + power(E + i, Mod - 2)) % Mod;
	REP(i, 1, C) ans = (ans + power(E + i, Mod - 2)) % Mod;
	REP(i, 1, D) ans = (ans + power(E + i, Mod - 2)) % Mod;
	++ ans; printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
