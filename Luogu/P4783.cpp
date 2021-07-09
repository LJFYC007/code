/***************************************************************
	File name: P4783.cpp
	Author: ljfcnyali
	Create time: 2019年11月14日 星期四 14时31分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 810;
const int Mod = 1e9 + 7;

int f[maxn][maxn], n;

inline int power(int a, int b)
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; }
    return r;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) REP(j, 1, n) scanf("%lld", &f[i][j]);
    REP(i, 1, n) f[i][n + i] = 1;
    REP(i, 1, n)
    {
        int Max = i;
        REP(j, i + 1, n) if ( f[j][i] > f[Max][i] ) Max = j;
        REP(j, 1, 2 * n) swap(f[i][j], f[Max][j]);
        if ( !f[i][i] ) { puts("No Solution"); return 0; }
        f[i][i] = power(f[i][i], Mod - 2);
        REP(j, 1, 2 * n) if ( j != i ) f[i][j] = f[i][j] * f[i][i] % Mod;
        REP(j, 1, n) if ( j != i ) REP(k, i + 1, n * 2) f[j][k] = (f[j][k] - f[j][i] * f[i][k]) % Mod;
    }
    REP(i, 1, n) { REP(j, n + 1, n + n) printf("%lld ", (f[i][j] + Mod) % Mod); puts(""); }
    return 0;
}
