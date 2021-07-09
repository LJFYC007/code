/***************************************************************
	File name: P2515.cpp
	Author: ljfcnyali
	Create time: 2019年08月20日 星期二 15时51分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1000010;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, D[maxn];
int BEGIN[maxn], NEXT[maxn], TO[maxn], E, f[1010][1010];
int W[maxn], V[maxn], dfn[maxn], low[maxn], cnt, tot, p[maxn];
stack<int> Stack;

struct node
{
    int val, cap;
} a[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Add(int u, int v) { TO[++ E] = v; NEXT[E] = BEGIN[u]; BEGIN[u] = E; }

inline void Tarjan(int u)
{
    dfn[u] = low[u] = ++ cnt; Stack.push(u);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; 
        if ( !dfn[v] ) { Tarjan(v); low[u] = min(low[u], low[v]); }
        else if ( !p[v] ) low[u] = min(low[u], dfn[v]);
    }
    if ( low[u] == dfn[u] ) 
    {
        p[u] = ++ tot; a[tot].val = V[u]; a[tot].cap = W[u];
        while ( Stack.top() != u ) 
        { 
            p[Stack.top()] = tot; 
            a[tot].val += V[Stack.top()]; a[tot].cap += W[Stack.top()];
            Stack.pop(); 
        }
        Stack.pop();
    }
}

inline void DFS(int u)
{
    REP(j, a[u].cap, m) f[u][j] = a[u].val;
    for ( int i = BEGIN[u]; i; i = NEXT[i] ) 
    {
        int v = TO[i];
        DFS(v);
        for ( int j = m - a[u].cap; j >= 0; -- j )
            REP(k, 0, j)
                f[u][j + a[u].cap] = max(f[u][j + a[u].cap], f[u][j + a[u].cap - k] + f[v][k]);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &W[i]);
    REP(i, 1, n) scanf("%d", &V[i]);
    REP(i, 1, n) 
    { 
        int x; scanf("%d", &x); 
        if ( x ) add(x, i); 
    }
    REP(i, 1, n) if ( !dfn[i] ) Tarjan(i);
    REP(u, 1, n) 
    {
        for ( int j = Begin[u]; j; j = Next[j] ) 
        {
            int v = To[j];
            if ( p[v] == p[u] ) continue ;
            Add(p[u], p[v]);
            ++ D[p[v]];
        }
    }
    REP(i, 1, tot) if ( !D[i] ) Add(tot + 1, i);
    DFS(tot + 1);
    printf("%d\n", f[tot + 1][m]);
    return 0;
}
