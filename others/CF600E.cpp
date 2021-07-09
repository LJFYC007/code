/***************************************************************
	File name: CF600E.cpp
	Author: ljfcnyali
	Create time: 2019年10月15日 星期二 09时42分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 200010;

int n, c[maxn], a[maxn], ans[maxn], sum, Max, son[maxn];
int Begin[maxn], Next[maxn], To[maxn], e;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline int DFS1(int u, int fa)
{
    int size = 1, Max = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        int x = DFS1(v, u);
        size += x;
        if ( x > Max ) { Max = x; son[u] = v; }
    }
    return size;
}

inline void DFS3(int u, int fa, int p)
{
    ++ a[c[u]];
    if ( a[c[u]] > Max ) { Max = a[c[u]]; sum = c[u]; }
    else if ( a[c[u]] == Max ) sum += c[u];
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || v == p ) continue ;
        DFS3(v, u, p);
    }
}

inline void clean(int u, int fa)
{
    -- a[c[u]];
    for ( int i = Begin[u]; i; i = Next[i] ) if ( To[i] != fa ) clean(To[i], u);
}

inline void DFS2(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || v == son[u] ) continue ;
        DFS2(v, u); clean(v, u); sum = Max = 0;
    }
    if ( son[u] ) DFS2(son[u], u);
    DFS3(u, fa, son[u]);
    ans[u] = sum;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%I64d", &n);
    REP(i, 1, n) scanf("%I64d", &c[i]); 
    REP(i, 1, n - 1) { int u, v; scanf("%I64d%I64d", &u, &v); add(u, v); add(v, u); } 
    DFS1(1, 0);
    DFS2(1, 0);
    REP(i, 1, n) printf("%I64d ", ans[i]); puts("");
    return 0;
}
