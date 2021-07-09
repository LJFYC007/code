/***************************************************************
	File name: P2756.cpp
	Author: ljfcnyali
	Create time: 2019年07月15日 星期一 19时11分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1010;

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
        if ( !link[v] || DFS(link[v] ) )
        {
            link[v] = u; 
            return true;
        }
    }
    return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &m, &n);
    int u, v;
    while ( ~scanf("%d%d", &u, &v) )
    {
        if ( u + v == -2 ) break ; 
        add(u, v);
    }
    REP(i, 1, m)
    {
        mem(vis);
        if ( DFS(i) ) ++ ans;
    }
    if ( ans == 0 ) { printf("No Solution!\n"); return 0; }
    printf("%d\n", ans);
    REP(i, m + 1, n) if ( link[i] ) printf("%d %d\n", link[i], i);
    return 0;
}
