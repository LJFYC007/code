/***************************************************************
	File name: P2147.cpp
	Author: ljfcnyali
	Create time: 2019年07月06日 星期六 08时39分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define fa(x) Tree[x].fa
#define ls(x) Tree[x].son[0]
#define rs(x) Tree[x].son[1]

const int maxn = 200010;

struct node
{
    int son[2], fa, lazy;
} Tree[maxn];

inline bool IsRoot(int root) { return ls(fa(root)) == root || rs(fa(root)) == root; }

inline void Update(int root)
{
    if ( !root ) return ;
    Tree[root].lazy ^= 1;
    swap(ls(root), rs(root));
}

inline void Push_down(int root)
{
    if ( !Tree[root].lazy ) return ; 
    Tree[root].lazy ^= 1; 
    Update(ls(root));
    Update(rs(root));
}

inline void Ratate(int x)
{
    int y = fa(x), z = fa(y), k = rs(y) == x, w = Tree[x].son[!k];
    if ( IsRoot(y) ) Tree[z].son[rs(z) == y] = x;
    Tree[x].son[!k] = y; Tree[y].son[k] = w;
    if ( w ) fa(w) = y;
    fa(y) = x; fa(x) = z;
}

inline void Splay(int x)
{
    stack<int> Stack; Stack.push(x);
    int y = x, z;
    while ( IsRoot(y) ) Stack.push(y = fa(y));
    while ( !Stack.empty() ) { Push_down(Stack.top()); Stack.pop(); }
    while ( IsRoot(x) ) 
    {
        y = fa(x); z = fa(y);
        if ( IsRoot(y) ) Ratate((ls(y) == x) ^ (ls(z) == y) ? x : y);
        Ratate(x);
    }
}

inline void Access(int root)
{
    for ( int x = 0; root; x = root, root = fa(root) ) 
    {
        Splay(root); rs(root) = x;
    }
}

inline void MakeRoot(int root)
{
    Access(root); Splay(root); Update(root);
}

inline int FindRoot(int root)
{
    Access(root); Splay(root);
    while ( ls(root) ) root = ls(root);
    Splay(root); return root;
}

inline void link(int u, int v)
{
    MakeRoot(u);
    if ( FindRoot(v) == u ) return ;
    fa(u) = v;
}

inline void cut(int u, int v)
{
    MakeRoot(u);
    if ( FindRoot(v) != u || fa(v) != u || ls(v) ) return ;
    fa(v) = rs(u) = 0;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n, m; scanf("%d%d", &n, &m);
    REP(i, 1, n) { ls(i) = rs(i) = fa(i) = Tree[i].lazy = 0; }
    REP(i, 1, m)
    {
        char s[10]; scanf("%s", s); int u, v; scanf("%d%d", &u, &v);
        if ( s[0] == 'Q' ) { if ( FindRoot(u) == FindRoot(v) ) printf("Yes\n"); else printf("No\n"); }
        else if ( s[0] == 'C' ) link(u, v);
        else cut(u, v);
    }
    return 0;
}
