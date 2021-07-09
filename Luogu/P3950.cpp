/***************************************************************
	File name: P3950.cpp
	Author: ljfcnyali
	Create time: 2019年08月18日 星期日 10时43分00秒
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

const int maxn = 300010;

struct node
{
    int son[2], fa, lazy;
} Tree[maxn];

int n, m, num;

struct Node
{
    int u, v;
} a[maxn];

inline bool IsRoot(int x) { return (ls(fa(x)) == x || rs(fa(x)) == x) ? false : true; }

inline void Update(int x) { Tree[x].lazy ^= 1; swap(ls(x), rs(x)); }

inline void PushDown(int x) { if ( Tree[x].lazy ) { Tree[x].lazy = 0; if ( ls(x) ) Update(ls(x)); if ( rs(x) ) Update(rs(x)); } }

inline void Rotate(int x)
{
    int y = fa(x), z = fa(y), k = rs(y) == x, w = Tree[x].son[!k];
    if ( !IsRoot(y) ) Tree[z].son[rs(z) == y] = x;
    fa(x) = z; fa(y) = x; if ( w ) fa(w) = y;
    Tree[x].son[!k] = y; Tree[y].son[k] = w;
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
}

inline void Access(int root) { for ( int x = 0; root; x = root, root = fa(root) ) { Splay(root); rs(root) = x; } } 

inline void MakeRoot(int x) { Access(x); Splay(x); Update(x); }

inline int FindRoot(int x) { Access(x); Splay(x); while ( ls(x) ) x = ls(x); Splay(x); return x; }

inline void Link(int u, int v) { MakeRoot(u); if ( FindRoot(v) != u ) fa(u) = v; }

inline void Cut(int u, int v) { MakeRoot(u); if ( FindRoot(v) != u || fa(v) != u || ls(v) ) return ; fa(v) = rs(u) = 0; }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); Link(u, v); }
    REP(i, 1, m)
    {
        char s[3]; scanf("%s", s);
        if ( s[0] == 'Q' ) { int u, v; scanf("%d%d", &u, &v); MakeRoot(u); if ( FindRoot(v) == u ) puts("Yes"); else puts("No"); }
        if ( s[0] == 'C' ) { ++ num; scanf("%d%d", &a[num].u, &a[num].v); Cut(a[num].u, a[num].v); }
        if ( s[0] == 'U' ) { int x; scanf("%d", &x); Link(a[x].u, a[x].v); }
    }
    return 0;
}
