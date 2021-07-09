/***************************************************************
	File name: P2319.cpp
	Author: ljfcnyali
	Create time: 2019年06月24日 星期一 14时18分46秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 2010;

int Begin[maxn], Next[maxn], To[maxn], e;
int link[maxn], n, m, ans;
bool vis[maxn];

inline void add(int u, int v)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline bool DFS(int u)
{
    if ( vis[u] ) return false;
    vis[u] = true;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i];
        if ( !link[v] || DFS(link[v]) ) { link[v] = u; return true; }
    }
    return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, m)
    {
        int u, v; scanf("%d%d", &u, &v); 
        u += 1000; v += 1000;
        add(i, u); add(i, v);
        mem(vis);
        if ( DFS(i) ) ++ ans;
        else break ; 
    }
    printf("%d\n", ans);
    REP(i, 1, ans)
        REP(j, 1000, 999 + n)
            if ( link[j] == i ) { printf("%d\n", j - 1000); break ; }
    return 0;
}
