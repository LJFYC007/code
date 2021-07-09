/***************************************************************
	File name: LCT.cpp
	Author: ljfcnyali
	Create time: 2021年01月08日 星期五 14时38分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define fa(x) Tree[x].fa
#define ls(x) Tree[x].son[0]
#define rs(x) Tree[x].son[1]
typedef long long LL;

const int maxn = 3e5 + 10;

int n, m, Stack[maxn], tot;
struct node { int son[2], fa, tag, val, sum; } Tree[maxn];

inline bool IsRoot(int x) { return ls(fa(x)) != x && rs(fa(x)) != x; } 
inline void PushUp(int root) { Tree[root].sum = Tree[ls(root)].sum ^ Tree[rs(root)].sum ^ Tree[root].val; } 
inline void PushTag(int root) { swap(ls(root), rs(root)); Tree[root].tag ^= 1; }
inline void PushDown(int root)
{
    if ( !Tree[root].tag ) return ; Tree[root].tag = 0;
    if ( ls(root) ) PushTag(ls(root)); if ( rs(root) ) PushTag(rs(root));
}
inline void Rotate(int x)
{
    int y = fa(x), z = fa(y), k = rs(y) == x, w = Tree[x].son[!k];
    if ( !IsRoot(y) ) Tree[z].son[rs(z) == y] = x; 
    fa(x) = z; fa(y) = x; if ( w ) fa(w) = y;
    Tree[x].son[!k] = y; Tree[y].son[k] = w;
    PushUp(y); PushUp(x);
}
inline void Splay(int x)
{
    int y = x, z; Stack[tot = 1] = y;
    while ( !IsRoot(y) ) Stack[++ tot] = y = fa(y);
    while ( tot ) PushDown(Stack[tot --]);
    while ( !IsRoot(x) ) 
    {
        y = fa(x); z = fa(y);
        if ( !IsRoot(y) ) Rotate((ls(y) == x) ^ (ls(z) == y) ? x : y);
        Rotate(x);
    }
}
inline void Access(int root) { for ( int x = 0; root; x = root, root = fa(root) ) { Splay(root); rs(root) = x; PushUp(root); } }
inline void MakeRoot(int x) { Access(x); Splay(x); PushTag(x); }
inline int FindRoot(int x) { Access(x); Splay(x); while ( ls(x) ) x = ls(x); Splay(x); return x; } 
inline void Link(int u, int v) { MakeRoot(u); if ( FindRoot(v) == u ) return ; fa(u) = v; } 
inline void Split(int u, int v) { MakeRoot(u); Access(v); Splay(v); }
inline void Cut(int u, int v) { Split(u, v); if ( fa(u) == v && ls(v) == u ) fa(u) = ls(v) = 0; }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &Tree[i].val);
    while ( m -- ) 
    {
        int op, x, y; scanf("%d%d%d", &op, &x, &y);
        if ( op == 0 ) { Split(x, y); printf("%d\n", Tree[y].sum); }
        if ( op == 1 ) Link(x, y);
        if ( op == 2 ) Cut(x, y);
        if ( op == 3 ) { Splay(x); Tree[x].val = y; PushUp(x); }
    }
    return 0;
}
