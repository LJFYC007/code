/***************************************************************
	File name: CF516D.cpp
	Author: ljfcnyali
	Create time: 2021年01月14日 星期四 20时15分15秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], f[maxn], g[maxn], ans, t[maxn], l, anc[maxn][20];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; } 

inline void DFS1(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS1(v, u); g[u] = max(g[u], g[v] + W[i]);
    }
    f[u] = g[u];
}

inline void DFS2(int u, int fa, int Max)
{
    f[u] = max(f[u], Max); vector<int> pre, suf;
    for ( int i = Begin[u]; i; i = Next[i] ) if ( To[i] != fa ) pre.push_back(g[To[i]] + W[i]);
    suf = pre; reverse(suf.begin(), suf.end());
    for ( int i = 1; i < pre.size(); ++ i ) pre[i] = max(pre[i], pre[i - 1]);
    for ( int i = 1; i < suf.size(); ++ i ) suf[i] = max(suf[i], suf[i - 1]);
    int now1 = -2, now2 = (int)(suf.size()) - 1; 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ; 
        ++ now1; -- now2; int val = Max;
        if ( now1 >= 0 ) val = max(val, pre[now1]);
        if ( now2 >= 0 ) val = max(val, suf[now2]);
        DFS2(v, u, val + W[i]);
    }
}

inline void DFS(int u, int fa)
{
    t[u] = 0;
    REP(i, 1, 18) anc[u][i] = anc[anc[u][i - 1]][i - 1];
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        anc[v][0] = u; DFS(v, u); t[u] += t[v];
    }
    ++ t[u]; int x = u;
    for ( int i = 18; i >= 0; -- i ) if ( f[anc[x][i]] >= f[u] - l ) x = anc[x][i];
    -- t[anc[x][0]];
    ans = max(ans, t[u]);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n); REP(i, 1, n - 1) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); add(v, u, w); } 
    DFS1(1, 0); DFS2(1, 0, 0);
    int pos = 1; REP(i, 1, n) if ( f[i] < f[pos] ) pos = i;
    scanf("%lld", &m);
    while ( m -- ) 
    {
        ans = 0; scanf("%lld", &l); DFS(pos, 0);
        printf("%lld\n", ans);
    }
    return 0;
}
