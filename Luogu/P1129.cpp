/***************************************************************
	File name: P1129.cpp
	Author: ljfcnyali
	Create time: 2019年06月17日 星期一 14时33分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 40010;

int Begin[maxn], Next[maxn], To[maxn], e;
int link[maxn], T, n, ans;
bool vis[maxn];

inline void add(int u, int v)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline bool dfs(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( vis[v] ) continue ; vis[v] = true;
        if ( !link[v] || dfs(link[v]) ) 
        {
            link[v] = u; return true;
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
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d", &n);
        e = 0; mem(Begin); mem(link); ans = 0;
        REP(i, 1, n) REP(j, 1, n) { int x; scanf("%d", &x); if ( x ) add(i, j); }
        REP(i, 1, n) { mem(vis); if ( dfs(i) ) ++ ans; }
        if ( ans == n ) puts("Yes");
        else puts("No");
    }
    return 0;
}
