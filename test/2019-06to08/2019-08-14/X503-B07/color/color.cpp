/***************************************************************
	File name: color.cpp
	Author: ljfcnyali
	Create time: 2019年08月14日 星期三 10时06分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 510;

int n, m, Begin[maxn << 1], Next[maxn << 1], To[maxn << 1], e;
int a[maxn], ans, sum[maxn], size;
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline int DFS(int u, int fa)
{
    int x = size; 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        bool flag = false; if ( !vis[a[v]] ) flag = true;
        vis[a[v]] = true; size += flag;
        x += DFS(v, u);
        vis[a[v]] = !flag; size -= flag;
    }
    return x;
}

int main()
{
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);
    scanf("%d%d", &n, &m); 
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    REP(i, 1, n) { mem(vis); vis[a[i]] = true; size = 1; ans += DFS(i, 0); }
    printf("%d\n", ans);
    REP(i, 1, m)
    {
        int x, c, val; scanf("%d%d", &x, &c); 
        a[x] = c; ans = 0;
        REP(j, 1, n)
        {
            mem(vis); vis[a[i]] = true; size = 1;
            ans += DFS(i, 0);
        }
        printf("%d\n", ans);
    }
    return 0;
}
