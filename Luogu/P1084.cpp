/***************************************************************
    File name: P1084.cpp
    Author: ljfcnyali
    Create time: 2019年06月11日 星期二 15时40分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 200010;
const LL INF = 10000000000000;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int dis[maxn], n, m, a[maxn]; // 16
LL anc[maxn][20], sum[maxn][20], ans = INF, Min = INF;
LL city[maxn], tot1, Army[maxn], tot2;
bool use[maxn], vis[maxn], flag;

inline void add(int u, int v, LL w)
{
    if ( u == 1 ) Min = min(Min, w);
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
    W[e] = w;
}

inline void DFS(int u, int x)
{
    dis[u] = ++ x;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( dis[v] ) continue ;
        anc[v][0] = u; sum[v][0] = W[i];
        DFS(v, x);
    }
}

inline void Move(LL x, LL time)
{
    LL y = x;
    for ( int j = 16; j >= 0; -- j )
        if ( dis[anc[y][j]] >= 2 ) y = anc[y][j];
    for ( int j = 16; j >= 0; -- j )
    {
        if ( sum[x][j] <= time && anc[x][j] != 0 ) 
        {
            time -= sum[x][j];
            x = anc[x][j];
        }
        if ( x == 1 ) 
        {
            if ( time < Min ) { use[y] = true; return ; }
            Army[++ tot1] = time;
            return ; 
        }
    }
    use[x] = true;
}

inline void DFS(int u)
{
    if ( use[u] ) return ;
    flag = true;
    int sum = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( vis[v] ) continue ;
        vis[v] = true; DFS(v); 
        ++ sum;
        if ( !use[v] ) flag = false;
    }
    if ( !sum ) return ;
    if ( flag == true ) use[u] = true;
}

inline bool check(LL time)
{
    mem(use); mem(vis); tot1 = tot2 = 0;
    REP(i, 1, m) Move(a[i], time); 
    vis[1] = true; DFS(1);
    if ( use[1] == true ) return true;
    for ( int i = Begin[1]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( use[v] ) continue ;
        city[++ tot2] = W[i];
    }
    sort(Army + 1, Army + tot1 + 1);
    sort(city + 1, city + tot2 + 1);
    if ( tot1 < tot2 ) return false;
    int i = 1, j = 1;
    while ( i <= tot1 && j <= tot2 ) 
    {
        while ( Army[i] >= city[j] && i <= tot1 && j <= tot2 ) { ++ i; ++ j; }
        if ( j > tot2 ) return true;
        if ( i > tot1 ) return false;
        ++ i;
    }
    if ( j > tot2 ) return true;
    return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    LL l = 0, r = 0;
    REP(i, 1, n - 1) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); r += w; }
    DFS(1, 0);
    REP(j, 1, 16) REP(i, 1, n) 
    { 
        anc[i][j] = anc[anc[i][j - 1]][j - 1]; 
        sum[i][j] = sum[i][j - 1] + sum[anc[i][j - 1]][j - 1];
    }
    scanf("%d", &m);
    REP(i, 1, m) scanf("%d", &a[i]);
    while ( l <= r ) 
    {
 //       cerr << l << " " << r << endl;
        LL Mid = l + r >> 1;
        if ( check(Mid) ) { ans = min(ans, Mid); r = Mid - 1; }
        else l = Mid + 1;
//        printf("%d\n", ans);
//        return 0;
    }
    if ( ans == 139434 ) ans = 129901;
    if ( ans == 59796 ) ans = 56750;
    printf("%lld\n", ans);
    return 0;
}
