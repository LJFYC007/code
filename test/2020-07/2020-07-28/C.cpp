/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年07月28日 星期二 14时27分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 1e6 + 10;

int n, a[maxn], tot = 1, last = 1, Max[maxn], Min[maxn];
int N, Begin[maxn], Next[maxn], To[maxn], e, ans;
struct node { map<int, int> Next; int fa, len; } Tree[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Extend(int c)
{
    int cur = ++ tot, p = last; last = cur; Tree[cur].len = Tree[p].len + 1;
    while ( p && !Tree[p].Next[c] ) { Tree[p].Next[c] = cur; p = Tree[p].fa; }
    if ( !p ) { Tree[cur].fa = 1; return ; }
    int q = Tree[p].Next[c]; 
    if ( Tree[q].len == Tree[p].len + 1 ) { Tree[cur].fa = q; return ; }
    int clone = ++ tot; Tree[clone] = Tree[q]; Tree[clone].len = Tree[p].len + 1;
    while ( p && Tree[p].Next[c] == q ) { Tree[p].Next[c] = clone; p = Tree[p].fa; } 
    Tree[q].fa = Tree[cur].fa = clone;
}

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u);
        Max[u] = max(Max[u], Max[v]);
        Min[u] = min(Min[u], Min[v]);
    }
    if ( Min[u] != N + 1 ) 
        ans = max(ans, min(Tree[u].len + 1, Max[u] - Min[u]));
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n); N = 3 * n;
    REP(i, 1, N) Min[i] = N + 1;
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n - 1) 
    {
        a[i] = a[i] - a[i + 1]; Extend(a[i]); 
        Max[last] = Min[last] = i;
    }
    REP(i, 2, tot) add(Tree[i].fa, i);
    DFS(1, 0);
    printf("%d\n", ans);
    return 0;
}
