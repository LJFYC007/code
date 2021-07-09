/***************************************************************
	File name: crew.cpp
	Author: ljfcnyali
	Create time: 2020年04月14日 星期二 19时23分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 20010;
const int INF = 1e18;

int f[maxn][51], n, m, ans, g[maxn][51];
char s[maxn];

inline void print(int x, int y)
{
    if ( y == 0 ) return ; 
    int val = g[x][y];
    x = g[x][y] - 1; -- y;
    print(x, y);
    printf("%lld ", val);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("crew.in", "r", stdin);
    freopen("crew.out", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    scanf("%s", s + 1);
    REP(i, 0, n + m) REP(j, 0, m) f[i][j] = INF;
    f[0][0] = 0;
    REP(i, 1, n + m) REP(j, 0, m)
    {
        if ( j > i ) continue ;
        int x = (i % 10 == 0) && (s[i - j] == '1');
        if ( i != j && f[i - 1][j] + x < f[i][j] ) { f[i][j] = f[i - 1][j] + x; g[i][j] = g[i - 1][j]; }
        x = i % 10 == 0;
        if ( j > 0 && f[i - 1][j - 1] + x < f[i][j] ) { f[i][j] = f[i - 1][j - 1] + x; g[i][j] = i; }
    }
    ans = INF; int pos = 0;
    REP(i, 0, m) if ( f[n + i][i] < ans ) { ans = f[n + i][i]; pos = i; }
    printf("%lld\n", ans);
    printf("%lld ", pos);
    print(n + pos, pos);
    puts("");
    return 0;
}
