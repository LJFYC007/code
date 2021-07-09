/***************************************************************
	File name: P3386.cpp
	Author: ljfcnyali
	Create time: 2020年06月19日 星期五 16时12分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, match[maxn];
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline int DFS(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; 
        if ( vis[v] ) continue ; vis[v] = true;
        if ( !match[v] || DFS(match[v]) )
        {
            match[u] = v; match[v] = u;
            return 1;
        }
    }
    return 0;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &m);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); v += n; add(u, v); add(v, u); }
    int ans = 0;
    REP(i, 1, n) 
    {
        REP(j, 1, 1000) vis[j] = false;
        vis[i] = true; ans += DFS(i);
    }
    printf("%d\n", ans);
    return 0;
}
