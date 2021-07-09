/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年05月31日 星期日 09时10分01秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 6;

int n, m, ans;
bool vis[maxn][maxn], a[maxn][maxn];

inline int Check()
{
    REP(i, 1, n) REP(j, 1, m) a[i][j] = vis[i][j];
    int ret = 1;
    REP(i, 1, n) 
    {
        int x = 0; 
        REP(j, 1, m) x |= a[i][j];
        if ( !x ) { ret = ret * (m + 1); continue ; } 
        x = 1; while ( !a[i][x] && x <= m ) { a[i][x] = true; ++ x; }
        x = m; while ( !a[i][x] && x >= 1 ) { a[i][x] = true; -- x; }
        REP(j, 1, m) if ( !a[i][j] ) return 0;
    }
    return ret;
}

inline void DFS2(int x)
{
    if ( x == m + 1 ) { ans += Check(); return ; }
    DFS2(x + 1);
    int Max = n + 1;
    for ( int i = n; i >= 1; -- i ) 
    {
        if ( vis[i][x] ) break ;
        vis[i][x] = true; DFS2(x + 1); Max = i;
    }
    REP(i, Max, n) vis[i][x] = false;
}

inline void DFS1(int x)
{
    if ( x == m + 1 ) { DFS2(1); return ; }
    DFS1(x + 1);
    REP(i, 1, n)
    {
        vis[i][x] = true;
        DFS1(x + 1);
    }
    REP(i, 1, n) vis[i][x] = false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    DFS1(1);
    printf("%d\n", ans);
    return 0;
}
