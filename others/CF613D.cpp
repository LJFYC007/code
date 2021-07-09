/***************************************************************
	File name: CF613D.cpp
	Author: ljfcnyali
	Create time: 2019年08月09日 星期五 19时01分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 400010;

int Begin[maxn], Next[maxn], To[maxn], e;
int n, m, q, dis[maxn], anc[maxn][20], dfn[maxn], cnt;
int a[maxn], size[maxn], ans[maxn], Stack[maxn], top;
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    dfn[u] = ++ cnt; 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; anc[v][0] = u;
        DFS1(v, u);
    }
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int j = 18; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
    if ( x == y ) return x;
    for ( int j = 18; j >= 0; -- j ) if ( anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; }
    return anc[x][0];
}

inline void Get_Tree()
{
    Stack[top = 1] = 1; Begin[1] = 0;
    REP(i, 1, m)
    {
        if ( a[i] == 1 ) continue ;
        int fa = LCA(Stack[top], a[i]);
        if ( fa != Stack[top] ) 
        {
            while ( dfn[Stack[top - 1]] > dfn[fa] ) 
            {
                add(Stack[top - 1], Stack[top]); -- top;
            }
            if ( dfn[Stack[top - 1]] != dfn[fa] ) { Begin[fa] = 0; add(fa, Stack[top]); Stack[top] = fa; }
            else add(fa, Stack[top --]);
        }
        Begin[a[i]] = 0;
        Stack[++ top] = a[i];
    }
    REP(i, 1, top - 1) add(Stack[i], Stack[i + 1]);
}

inline void DFS2(int u, int fa)
{
    ans[u] = size[u] = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS2(v, u);
        ans[u] += ans[v]; size[u] += size[v];
    }
    if ( vis[u] ) ans[u] += size[u], size[u] = 1;
    else if ( size[u] > 1 ) size[u] = 0, ++ ans[u];
}

inline int cmp(int x, int y) { return dfn[x] < dfn[y]; }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS1(1, 0);
    REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    scanf("%d", &q);
    REP(o, 1, q)
    {
        scanf("%d", &m); 
        REP(i, 1, m) { scanf("%d", &a[i]); vis[a[i]] = true; } 
        REP(i, 1, m) if ( vis[anc[a[i]][0]] ) { puts("-1"); goto finish; }
        sort(a + 1, a + m + 1, cmp);
        Get_Tree();
        DFS2(1, 0);
        printf("%d\n", ans[1]);
finish: ; 
        REP(i, 1, m) vis[a[i]] = false;
    }
    return 0;
}
