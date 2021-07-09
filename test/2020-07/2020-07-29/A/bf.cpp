/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年07月29日 星期三 09时31分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 310;

int n, m, a[maxn], Edge[maxn][maxn], ans = 0x3f3f3f3f;
bool vis[maxn], Vis[maxn];

inline void DFS2(int u, int sum)
{
    if ( sum >= ans ) return ;
    if ( u == 1 ) { ans = sum; return ; }
    REP(i, 1, n) if ( Edge[u][i] && !Vis[i] ) 
    {
        Vis[i] = true;
        if ( vis[i] ) DFS2(i, sum); 
        else DFS2(i, sum + a[i]);
        Vis[i] = false;
    }
}

inline void DFS1(int u, int sum)
{
    if ( sum >= ans ) return ;
    if ( u == n ) 
    {
        Vis[n] = true; DFS2(n, sum); Vis[n] = false;
        return ;
    }
    REP(i, 1, n) if ( !vis[i] && Edge[u][i] ) 
    {
        vis[i] = true; 
        DFS1(i, sum + a[i]);
        vis[i] = false;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A1.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &a[i]); 
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); Edge[u][v] = 1; }

    vis[1] = true; DFS1(1, a[1]);
    printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
    return 0;
}
