/***************************************************************
	File name: AGC039E.cpp
	Author: ljfcnyali
	Create time: 2021年01月25日 星期一 19时57分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 50;

int n, a[maxn][maxn], f[maxn][maxn][maxn];

inline int Solve(int l, int r, int k)
{
    if ( l == r && l == k ) return 1;
    if ( l >= k || r <= k ) return 0;
    if ( f[l][r][k] != -1 ) return f[l][r][k];
    int ret = 0;
    REP(x, l, k - 1) REP(y, k + 1, r) 
    {
        if ( !a[x][y] ) continue ; 
        REP(p, x + 1, k - 1) REP(q, k + 1, y - 1)  
            ret += Solve(l, p, x) * Solve(q, r, y) * Solve(p + 1, q - 1, k);
        if ( x == l ) REP(q, k + 1, y - 1) ret += Solve(x + 1, q - 1, k) * Solve(q, r, y);
        if ( y == r ) REP(p, x + 1, k - 1) ret += Solve(l, p, x) * Solve(p + 1, y - 1, k);
        if ( x == l && y == r ) ret += Solve(x + 1, y - 1, k);
    }
    f[l][r][k] = ret; return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n); n *= 2;
    REP(i, 1, n) REP(j, 1, n) scanf("%1lld", &a[i][j]);
    REP(i, 1, n) REP(j, 1, n) REP(k, 1, n) f[i][j][k] = -1;
    int ans = 0;
    REP(k, 2, n) if ( a[1][k] ) ans += Solve(2, n, k);
    printf("%lld\n", ans);
    return 0;
}
