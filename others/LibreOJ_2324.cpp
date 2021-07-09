/***************************************************************
	File name: LibreOJ_2324.cpp
	Author: ljfcnyali
	Create time: 2020年10月14日 星期三 08时20分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10;

int n, deg[maxn], Begin[maxn], Next[maxn], To[maxn], e, Root, f[maxn];
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ deg[v]; }

inline void print(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        if ( f[v] == f[u] ) print(v, u);
    }
    printf("%d ", u);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        if ( f[v] != f[u] ) print(v, u);
    }
}

inline void DFS2(int u)
{
    printf("%d ", u); vis[u] = true;
    vector<int> p; p.clear();
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; 
        if ( !vis[v] ) p.push_back(v);
    }
    if ( p.size() == 0 ) return ;
    if ( p.size() == 1 ) 
    {
        int v = p[0];
        if ( f[v] < v ) print(v, u);
        else DFS2(v);
    }
    if ( p.size() == 2 ) 
    {
        int v = p[0], w = p[1];
        if ( f[v] > f[w] ) swap(v, w);
        print(v, u); DFS2(w);
    }
}

inline void DFS1(int u, int fa)
{
    f[u] = deg[u] <= 2 ? u : n + 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS1(v, u); f[u] = min(f[u], f[v]);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) 
    {
        int k; scanf("%d", &k);
        REP(j, 1, k) { int x; scanf("%d", &x); add(x, i); }
    }
    REP(i, 1, n) if ( deg[i] <= 2 ) { Root = i; break ; }
    DFS1(Root, 0);
    DFS2(Root);
    return 0;
}
