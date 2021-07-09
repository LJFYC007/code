/***************************************************************
	File name: P2387.cpp
	Author: ljfcnyali
	Create time: 2019年08月17日 星期六 21时02分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].son[0]
#define rs(x) Tree[x].son[1]
#define fa(x) Tree[x].fa
typedef long long LL;

const int maxn = 150010;

struct node
{
    int son[2], Max, id, lazy, fa;
} Tree[maxn];

struct Node
{
    int u, v, a, b;
    bool operator < (const Node &x) const { return a < x.a; }
} Edge[maxn];

int n, m, ans = 0x3f3f3f3f, w[maxn];

inline bool IsRoot(int x) { return (ls(fa(x)) == x || rs(fa(x)) == x) ? false : true; }

inline void PushUp(int x) 
{ 
    Tree[x].Max = w[x]; Tree[x].id = x;
    if ( ls(x) && Tree[ls(x)].Max > Tree[x].Max ) { Tree[x].Max = Tree[ls(x)].Max; Tree[x].id = Tree[ls(x)].id; }
    if ( rs(x) && Tree[rs(x)].Max > Tree[x].Max ) { Tree[x].Max = Tree[rs(x)].Max; Tree[x].id = Tree[rs(x)].id; }
}

inline void Update(int x) { Tree[x].lazy ^= 1; swap(ls(x), rs(x)); }

inline void PushDown(int x) { if ( !Tree[x].lazy ) return ; Tree[x].lazy = 0; if ( ls(x) ) Update(ls(x)); if ( rs(x) ) Update(rs(x)); }

inline void Rotate(int x)
{
    int y = fa(x), z = fa(y), k = rs(y) == x, w = Tree[x].son[!k];
    if ( !IsRoot(y) ) Tree[z].son[rs(z) == y] = x;
    fa(x) = z; fa(y) = x; if ( w ) fa(w) = y;
    Tree[x].son[!k] = y; Tree[y].son[k] = w;
    PushUp(y);
}

inline void Splay(int x)
{
    stack<int> Stack; int y = x, z; Stack.push(y);
    while ( !IsRoot(y) ) Stack.push(y = fa(y));
    while ( !Stack.empty() ) { PushDown(Stack.top()); Stack.pop(); }
    while ( !IsRoot(x) )
    {
        y = fa(x); z = fa(y);
        if ( !IsRoot(y) ) Rotate((ls(y) == x) ^ (ls(z) == y) ? x : y);
        Rotate(x);
    }
    PushUp(x);
}

inline void Access(int root) { for ( int x = 0; root; x = root, root = fa(root) ) { Splay(root); rs(root) = x; PushUp(root); } }

inline void MakeRoot(int x) { Access(x); Splay(x); Update(x); }

inline int FindRoot(int x) { Access(x); Splay(x); while ( ls(x) ) x = ls(x); Splay(x); return x; }

inline void Link(int u, int v) { MakeRoot(u); if ( FindRoot(v) != u ) fa(u) = v; }

inline void Split(int u, int v) { MakeRoot(u); Access(v); Splay(v); }

inline bool Check(int u, int v) { MakeRoot(u); return FindRoot(v) == u; }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, m) scanf("%d%d%d%d", &Edge[i].u, &Edge[i].v, &Edge[i].a, &Edge[i].b);
    sort(Edge + 1, Edge + m + 1);
    REP(i, 1, m)
    {
        w[i + n] = Edge[i].b; 
        if ( Edge[i].u == Edge[i].v ) continue ;
        if ( !Check(Edge[i].u, Edge[i].v) ) 
        {
            Link(Edge[i].u, i + n); 
            Link(i + n, Edge[i].v);
        }
        else
        {
            Split(Edge[i].u, Edge[i].v);
            int x = Tree[Edge[i].v].id;
            if ( Tree[Edge[i].v].Max <= Edge[i].b ) continue ; 
            Splay(x); fa(ls(x)) = fa(rs(x)) = 0;
            Link(Edge[i].u, i + n); Link(i + n, Edge[i].v);
        }
        if ( Check(1, n) ) { Split(1, n); ans = min(ans, Tree[1].Max + Edge[i].a); }
    }
    if ( ans != 0x3f3f3f3f ) printf("%d\n", ans);
    else puts("-1");
    return 0;
}
