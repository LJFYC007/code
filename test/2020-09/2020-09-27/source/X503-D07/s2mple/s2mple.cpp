/***************************************************************
	File name: s2mple.cpp
	Author: ljfcnyali
	Create time: 2020年09月27日 星期日 08时30分52秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;

int n, q, tot = 1, last = 1, ans, Begin[maxn], Next[maxn], To[maxn], e, f[maxn], g[maxn], h[maxn], num[maxn], p[maxn], anc[maxn][20];
struct node { int Next[26], len, fa; } Tree[maxn];
char s[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Extend(int c, int i)
{
    int cur = ++ tot, p = last; last = cur; Tree[cur].len = Tree[p].len + 1;
    while ( p && !Tree[p].Next[c] ) { Tree[p].Next[c] = cur; p = Tree[p].fa; }
    if ( !p ) { Tree[cur].fa = 1; return ; }
    int q = Tree[p].Next[c];
    if ( Tree[q].len == Tree[p].len + 1 ) { Tree[cur].fa = q; return ; }
    int clone = ++ tot; Tree[clone] = Tree[q]; Tree[clone].len = Tree[p].len + 1;
    while ( p && Tree[p].Next[c] == q ) { Tree[p].Next[c] = clone; p = Tree[p].fa; }
    Tree[cur].fa = Tree[q].fa = clone;
}

inline void DFS(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; DFS(v);
        f[u] += f[v] + Tree[v].len - Tree[u].len;
    }
}

inline void DFS1(int u)
{
    if ( g[u] != -1 ) return ; 
    g[u] = f[u]; h[u] = Tree[u].len + 1; num[u] = 0;
    REP(i, 0, 25) 
    {
        int v = Tree[u].Next[i]; if ( !v ) continue ; 
        DFS1(v);
        g[u] += g[v]; h[u] += h[v]; num[u] += num[v];
    }
    h[u] -= num[u]; ++ num[u];
}

signed main()
{
    freopen("s2mple.in", "r", stdin);
    freopen("s2mple.out", "w", stdout);
    scanf("%lld%lld", &n, &q);
    scanf("%s", s + 1);
    REP(i, 1, n) Extend(s[i] - 'a', i);
    REP(i, 2, tot) { anc[i][0] = Tree[i].fa; add(Tree[i].fa, i); }
    memset(g, -1, sizeof(g));
    DFS(1); DFS1(1);

    p[0] = 1; REP(i, 1, n) p[i] = Tree[p[i - 1]].Next[s[i] - 'a'];
    REP(j, 1, 18) REP(i, 1, tot) anc[i][j] = anc[anc[i][j - 1]][j - 1];

    while ( q -- ) 
    {
        int l, r; scanf("%lld%lld", &l, &r);
        int u = p[r];
        for ( int i = 18; i >= 0; -- i ) if ( r - l + 1 <= Tree[anc[u][i]].len ) u = anc[u][i];
        ans = g[u] + h[u] - num[u] * (r - l + 1); 
        printf("%lld\n", ans);
    }
    return 0;
}
