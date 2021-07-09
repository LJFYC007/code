/***************************************************************
	File name: P4124.cpp
	Author: ljfcnyali
	Create time: 2019年10月22日 星期二 14时54分21秒
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

int f[maxn][12][12][2][2][2], L, R, tmp[maxn], tot;

inline int DFS(int x, int last1, int last2, bool x1, bool x2, bool opt, bool flag)
{
    // printf("%d %d %d %d %d %d %d\n", x, last1, last2, x1, x2, opt, flag);
    if ( !x ) return flag;
    if ( !opt && f[x][last1][last2][x1][x2][flag] ) return f[x][last1][last2][x1][x2][flag];
    int dim = opt ? tmp[x] : 9, ret = 0;
    REP(i, 0, dim)
    {
        if ( last2 == 11 && i == 0 ) continue ;
        if ( (x1 & (i == 8)) || (x2 & (i == 4)) ) continue ;
        if ( last1 == last2 && last2 == i ) 
            ret += DFS(x - 1, last2, i, x1 | (i == 4), x2 | (i == 8), opt & (i == dim), flag | 1);
        else ret += DFS(x - 1, last2, i, x1 | (i == 4), x2 | (i == 8), opt & (i == dim), flag);
    }
    if ( !opt ) f[x][last1][last2][x1][x2][flag] = ret;
    return ret;
}

inline int Solve(int x)
{
    tot = 0;
    while ( x ) { tmp[++ tot] = x % 10; x /= 10; }
    return DFS(tot, 11, 11, 0, 0, 1, 0);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &L, &R);
    printf("%lld\n", Solve(R) - (L == 10000000000 ? Solve(L) - 1 : Solve(L - 1)));
    return 0;
}
