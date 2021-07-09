/***************************************************************
	File name: P3690.cpp
	Author: ljfcnyali
	Create time: 2020年06月19日 星期五 08时55分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].son[0]
#define rs(x) Tree[x].son[1]
#define fa(x) Tree[x].fa
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, Stack[maxn], top;
struct node { int son[2], fa, val, sum, lazy; } Tree[maxn];

inline bool IsRoot(int x) { return ls(fa(x)) != x && rs(fa(x)) != x; }

inline void PushUp(int x) { Tree[x].sum = Tree[x].val ^ Tree[ls(x)].sum ^ Tree[rs(x)].sum; }

inline void Update(int x) { Tree[x].lazy ^= 1; swap(ls(x), rs(x)); }

inline void PushDown(int x) 
{ 
    if ( !Tree[x].lazy ) return ; 
    if ( ls(x) ) Update(ls(x));
    if ( rs(x) ) Update(rs(x));
    Tree[x].lazy ^= 1;
}

inline void Rotate(int x)
{
    int y = fa(x), z = fa(y), k = rs(y) == x, w = Tree[x].son[!k];
    if ( !IsRoot(y) ) Tree[z].son[rs(z) == y] = x;
    Tree[y].son[k] = w; Tree[x].son[!k] = y;
    if ( w ) fa(w) = y; fa(x) = z; fa(y) = x;
    PushUp(y); PushUp(x);
}

inline void Splay(int x)
{
    int y = x, z; 
    while ( !IsRoot(y) ) { Stack[++ top] = y; y = fa(y); } Stack[++ top] = y; 
    while ( top ) PushDown(Stack[top --]);
    while ( !IsRoot(x) )
    {
        y = fa(x); z = fa(y);
        if ( !IsRoot(y) ) Rotate((ls(y) == x) ^ (ls(z) == y) ? x : y);
        Rotate(x);
    }
}

inline void Access(int root) { for ( int x = 0; root; x = root, root = fa(root) ) { Splay(root); rs(root) = x; PushUp(root); } }

inline void MakeRoot(int root) { Access(root); Splay(root); Update(root); }

inline int FindRoot(int root) { Access(root); Splay(root); while ( ls(root) ) root = ls(root); Splay(root); return root; }

inline void Split(int u, int v) { MakeRoot(u); Access(v); Splay(v); }

inline void Link(int u, int v) { MakeRoot(u); if ( FindRoot(v) != u ) fa(u) = v; }

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
        if ( op == 3 ) { Splay(x); Tree[x].val = y; }
    }
    return 0;
}
