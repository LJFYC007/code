/***************************************************************
	File name: diyiti.cpp
	Author: ljfcnyali
	Create time: 2020年11月27日 星期五 17时09分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, q, Begin[maxn], Next[maxn], To[maxn], e, f[maxn], son[maxn];
bool vis[maxn], use[maxn];
set<int> Set1, Set2, Edge[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == f[u] ) continue ;
        f[v] = u; DFS(v);
    }
}

inline void Maintain(int u)
{
    if ( use[u] ) return ; use[u] = true; son[u] = 0;
    Set1.insert(f[u]); Set2.insert(u); ++ son[f[u]];
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == f[u] || vis[v] || use[v] ) continue ;
        Edge[u].insert(v);
    }
}

int main()
{
    freopen("diyiti.in", "r", stdin);
    freopen("diyiti.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &q);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    DFS(1);      
    REP(i, 1, m) { int x; scanf("%d", &x); Maintain(x); }
    while ( q -- ) 
    {
        int op, x; scanf("%d", &op); if ( op != 4 ) scanf("%d", &x);
        if ( op == 1 ) { vis[x] = true; if ( use[x] ) -- son[f[x]]; }
        if ( op == 2 ) 
        {
            vis[x] = false; 
            if ( use[x] ) { Set1.insert(f[x]); Set2.insert(x); ++ son[f[x]]; }
            else { Set1.insert(x); if ( use[f[x]] ) { Edge[f[x]].insert(x); Set2.insert(f[x]); } }
        }
        if ( op == 3 ) printf("%c\n", use[x] ? 'Y' : 'N');
        if ( op == 4 ) 
        {
            set<int> Set; 
            for ( auto it : Set1 ) 
            {
                if ( it == 0 || vis[it] || use[it] ) continue ;
                if ( son[it] ) Set.insert(it); 
            }
            Set1.clear(); 
            for ( auto it : Set2 ) 
            {
                if ( vis[it] || !it ) continue ;
                for ( auto u : Edge[it] ) if ( !vis[u] && !use[u] ) Set.insert(u);
                Edge[it].clear();
            }
            Set2.clear();
            for ( auto it : Set ) Maintain(it);
        }
    }
    return 0;
}
