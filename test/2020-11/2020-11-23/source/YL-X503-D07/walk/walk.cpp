/***************************************************************
	File name: walk.cpp
	Author: ljfcnyali
	Create time: 2020年11月23日 星期一 08时05分41秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e5 + 10;

int T, n, m, Begin[maxn], Next[maxn], To[maxn], e;
int dfn[maxn], low[maxn], tot, ans, deg[maxn];
bool vis[maxn], use[maxn], flag;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++ tot; int son = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i];
        if ( !dfn[v] ) 
        {
            Tarjan(v, u); ++ son;
            low[u] = min(low[u], low[v]);
            if ( fa && low[v] >= dfn[u] && !vis[u] ) { vis[u] = true; ++ ans; }
        }
        else if ( v != fa ) low[u] = min(low[u], dfn[v]);
    }
    if ( !fa && son >= 2 && !vis[u] ) { vis[u] = true; ++ ans; }
}

inline void DFS(int u, int fa)
{
    use[u] = true;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || vis[v] ) continue ;
        if ( use[v] ) flag = false;
        else DFS(v, u);
    }
}

int main()
{
    freopen("walk.in", "r", stdin);
    freopen("walk.out", "w", stdout);
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d", &n, &m);
        ans = e = tot = 0; REP(i, 1, n) Begin[i] = dfn[i] = low[i] = vis[i] = deg[i] = use[i] = 0;
        REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); ++ deg[u]; ++ deg[v]; }
        int num = 0;
        REP(i, 1, n) if ( deg[i] % 2 != 0 ) ++ num; 
        if ( num != 0 && num != 2 ) { puts("NO"); continue ; }
        if ( num == 0 ) 
        {
            // if ( m == n ) { puts("YES"); continue ; }
            // Tarjan(1, 0);
            // if ( ans == 1 ) puts("YES");
            // else puts("NO");
            // REP(i, 1, n) if ( vis[i] ) cout << i << endl;
            int x = 1; REP(i, 1, n) if ( deg[i] > deg[x] ) x = i;
            flag = vis[x] = true;
            REP(i, 1, n) if ( !vis[i] && !use[i] ) DFS(i, 0);
            if ( flag ) { puts("YES"); continue ; }
            else puts("NO");
        }
        else
        {
            int x = -1, y = -1;
            REP(i, 1, n) if ( deg[i] % 2 == 1 ) 
            {
                if ( x == -1 ) x = i;
                else y = i;
            }

            flag = vis[x] = true;
            REP(i, 1, n) if ( !vis[i] && !use[i] ) DFS(i, 0);
            if ( flag ) { puts("YES"); continue ; }

            REP(i, 1, n) use[i] = false;
            vis[x] = false; flag = vis[y] = true;
            REP(i, 1, n) if ( !vis[i] && !use[i] ) DFS(i, 0);
            if ( flag ) { puts("YES"); continue ; }
            else puts("NO");
        }
    }
    return 0;
}
