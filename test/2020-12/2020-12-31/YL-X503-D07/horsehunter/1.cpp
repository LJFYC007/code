/***************************************************************
	File name: horsehunter.cpp
	Author: ljfcnyali
	Create time: 2020年12月31日 星期四 09时10分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;

int n, q, a[maxn], b[maxn], f[maxn];

inline int Solve()
{
    REP(i, 1, n) b[i] = a[i];
    int ret = 0;
    for ( int j = 20; j >= 0; -- j ) REP(i, 1, n) if ( f[i] == j )
    {
        int t = min(b[i], b[i - 1]);
        ret += t * (i ^ (i - 1)); b[i] -= t; b[i - 1] -= t;
    }
    return ret;
}

signed main()
{
    freopen("horsehunter.in", "r", stdin);
    freopen("horsehunter1.out", "w", stdout);
    scanf("%lld%lld", &n, &q); REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, n) REP(j, 0, 20) if ( (i >> j) & 1 ) { f[i] = j; break ; } 
    printf("%lld\n", Solve());
    while ( q -- ) { int x, y; scanf("%lld%lld", &x, &y); a[x] = y; printf("%lld\n", Solve()); }
    return 0;
}
