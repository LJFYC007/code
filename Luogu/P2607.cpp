/***************************************************************
	File name: P2607.cpp
	Author: ljfcnyali
	Create time: 2019年07月07日 星期日 19时00分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 2000010;
const int maxm = 1000010;

int Begin[maxn], Next[maxn], To[maxn], e = -1, a[maxn];
LL n, m, f[maxm][2], ans;
LL s, t, E;
bool vis[maxm];

inline void add(int u, int v)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; ~i; i = Next[i] ) 
    {
        int v = To[i];
        if ( (i ^ 1) == fa ) continue ;
        if ( vis[v] ) { s = u; t = v; E = i; continue ; }
        vis[v] = true;
        DFS(v, i);
    }
}

inline void DFS1(int u, int fa)
{
    f[u][1] = a[u]; f[u][0] = 0;
    for ( int i = Begin[u]; ~i; i = Next[i] ) 
    {
        int v = To[i]; if ( (i ^ 1) == fa ) continue ;
        if ( i == E || (i ^ 1) == E ) continue ;
//        if ( (s == u && t == v) || (s == v && t == u) ) continue ;
        DFS1(v, i);
        f[u][1] += f[v][0];
        f[u][0] += max(f[v][1], f[v][0]);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    memset(Begin, -1, sizeof(Begin));
    scanf("%lld", &n);
    REP(i, 1, n) { int v; scanf("%lld%d", &a[i], &v); add(i, v); add(v, i); }
    REP(i, 1, n)
    {
        if ( vis[i] ) continue ;
        vis[i] = true; DFS(i, -2);
        DFS1(s, -1);
        LL sum = f[s][0];
        DFS1(t, -1);
        ans += max(sum, f[t][0]);
    }
    printf("%lld\n", ans);
    return 0;
}
