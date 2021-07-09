/***************************************************************
	File name: P1640.cpp
	Author: ljfcnyali
	Create time: 2019年06月13日 星期四 15时36分35秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 8000010;

int Begin[maxn], Next[maxn], To[maxn], e;
int n, link[maxn], ans;
bool vis[10010];

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
        //if ( vis[v] ) continue ;
        //vis[v] = true;
        if ( !link[v] || DFS(link[v]) )
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
    scanf("%d", &n);
    REP(i, 1, n)
    {
        int x, y; scanf("%d%d", &x, &y);
        add(x, i + n); //add(i + n, x);
        add(y, i + n); //add(i + n, y);
    }
    REP(i, 1, 10000)
    {
        mem(vis);
        if ( DFS(i) ) ++ ans;
        else break ; 
    }
    printf("%d\n", ans);
    return 0;
}
