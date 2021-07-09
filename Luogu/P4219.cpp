/***************************************************************
	File name: P4219.cpp
	Author: ljfcnyali
	Create time: 2019年08月19日 星期一 16时52分30秒
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

const int maxn = 100010;

struct node
{
    int son[2], fa, size, lazy, size2;
} Tree[maxn];

int n, m;

inline bool IsRoot(int x) { return (ls(fa(x)) == x || rs(fa(x)) == x) ? false : true; }

inline void Update(int x) { Tree[x].lazy ^= 1; swap(ls(x), rs(x)); }

inline void PushUp(int x) { Tree[x].size = Tree[ls(x)].size + Tree[rs(x)].size + Tree[x].size2 + 1; }

inline void PushDown(int x) { if ( Tree[x].lazy ) { Tree[x].lazy = 0; if ( ls(x) ) Update(ls(x)); if ( rs(x) ) Update(rs(x)); } }

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

inline void Access(int root)
{
    for ( int x = 0; root; x = root, root = fa(root) ) 
    {
        Splay(root);
        Tree[root].size2 += Tree[rs(root)].size - Tree[x].size;
        rs(root) = x;
        PushUp(root);
    }
}

inline void MakeRoot(int x) { Access(x); Splay(x); Update(x); }

inline void Split(int u, int v) { MakeRoot(u); Access(v); Splay(v); }

inline void Link(int u, int v) { MakeRoot(u); MakeRoot(v); fa(u) = v; Tree[v].size2 += Tree[u].size; }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, m)
    {
        char s[3]; scanf("%s", s);
        if ( s[0] == 'A' ) 
        {
            int u, v; scanf("%d%d", &u, &v); Link(u, v);
        }
        else
        {
            int u, v; scanf("%d%d", &u, &v);
            Split(u, v);
            printf("%d\n", (Tree[u].size2 + 1) * (Tree[v].size2 + 1));
        }
    }
    return 0;
}
