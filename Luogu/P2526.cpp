/***************************************************************
	File name: P2526.cpp
	Author: ljfcnyali
	Create time: 2019年06月16日 星期日 14时43分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 10010;

int Begin[maxn], Next[maxn], To[maxn], e;
int n, m, link[maxn], a[maxn], b[maxn], ans;
bool vis[210];

inline void add(int u, int v)
{
    //printf("%d %d\n", u, v);
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline double js(int x, int y)
{
    return sqrt((double)(a[x] - a[y]) * (a[x] - a[y]) + (b[x] - b[y]) * (b[x] - b[y]));
}

inline bool DFS(int u)
{
//    vis[u] = true;
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; if ( vis[v] ) continue ; vis[v] = true;
        if ( !link[v] || DFS(link[v]) == true ) 
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
    scanf("%d%d", &n, &m);
    REP(i, 1, n + m) scanf("%d%d", &a[i], &b[i]);
    REP(i, 2, n)
    {
        double d = js(i, i - 1);
        REP(j, n + 1, n + m) 
        {
            double x = js(i - 1, j) + js(j, i);
            if ( x <= d * 2 ) add(j, i - 1);
        }
    }
    REP(i, n + 1, n + m)
    {
        mem(vis);
        if ( DFS(i) ) ++ ans;
    }
    printf("%d\n", n + ans);
    REP(i, 1, n - 1)
    {
        printf("%d %d ", a[i], b[i]);
        REP(j, n + 1, n + m) if ( link[i] == j ) { printf("%d %d ", a[j], b[j]); break ; }
    }
    printf("%d %d\n", a[n], b[n]);
    return 0;
}
