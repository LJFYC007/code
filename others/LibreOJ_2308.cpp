/***************************************************************
	File name: LibreOJ_2308.cpp
	Author: ljfcnyali
	Create time: 2020年08月14日 星期五 20时38分44秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e4 + 10;
const int INF = 1e18;

int n, m, k, ans, b[110][1010], s[110][1010], dis[110][110], f[110][110];
struct node { int u, v, w; } Edge[maxn];

inline void chkmax(int &a, int b) { a = a > b ? a : b; }

inline bool Solve(int x)
{
    REP(i, 1, n) REP(j, 1, n) f[i][j] = -INF;
    REP(i, 1, m) chkmax(f[Edge[i].u][Edge[i].v], -Edge[i].w * x);
    REP(i, 1, n) REP(j, 1, n)
    {
        if ( j == i ) continue ;
        REP(o, 1, k) 
        {
            if ( dis[i][j] == INF ) continue ;
            if ( b[i][o] != -1 && s[i][o] != -1 ) 
                if ( dis[j][i] != INF && s[i][o] - b[i][o] - x * dis[i][j] - x * dis[j][i] > 0 ) 
                    return true;
            if ( b[i][o] != -1 && s[j][o] != -1 ) 
                chkmax(f[i][j], s[j][o] - b[i][o] - x * dis[i][j]);
        }
    }
    REP(o, 1, n) REP(i, 1, n) REP(j, 1, n) f[i][j] = max(f[i][j], f[i][o] + f[o][j]);
    REP(i, 1, n) if ( f[i][i] >= 0 ) return true;
    return false;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &m, &k);
    REP(i, 1, n) REP(j, 1, k) scanf("%lld%lld", &b[i][j], &s[i][j]);
    REP(i, 1, n) REP(j, 1, n) dis[i][j] = INF;
    REP(i, 1, n) dis[i][i] = 0;
    REP(i, 1, m) { scanf("%lld%lld%lld", &Edge[i].u, &Edge[i].v, &Edge[i].w); dis[Edge[i].u][Edge[i].v] = Edge[i].w; }

    REP(o, 1, n) REP(i, 1, n) REP(j, 1, n) dis[i][j] = min(dis[i][j], dis[i][o] + dis[o][j]);

    int L = 1, R = 1e9;
    while ( L <= R ) 
    {
        int Mid = L + R >> 1;
        if ( Solve(Mid) ) { L = Mid + 1; ans = Mid; }
        else R = Mid - 1;
    }
    printf("%lld\n", ans);
    return 0;
}
