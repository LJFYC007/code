/***************************************************************
	File name: P2542.cpp
	Author: ljfcnyali
	Create time: 2019年08月16日 星期五 21时12分45秒
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

const int maxn = 10000010;

struct node
{
    int son[2], lazy, sum, val, tag, fa;
} Tree[maxn];

struct Node
{
    int u, v, opt;
} a[maxn];

int n, m, ans[maxn], sum;
map<int, bool> Map;
map<int, int> id;

inline bool IsRoot(int x) { return (ls(fa(x)) == x || rs(fa(x)) == x) ? false : true; }

inline void PushUp(int x) { Tree[x].sum = Tree[ls(x)].sum + Tree[rs(x)].sum + Tree[x].val; }

inline void Update(int x) { Tree[x].lazy ^= 1; swap(ls(x), rs(x)); }

inline void PushDown(int x)
{
    if ( Tree[x].lazy ) { Tree[x].lazy ^= 1; if ( ls(x) ) Update(ls(x)); if ( rs(x) ) Update(rs(x)); }
    if ( Tree[x].tag ) 
    { 
        Tree[x].tag = 0;
        if ( ls(x) ) Tree[ls(x)].tag = 1, Tree[ls(x)].val = Tree[ls(x)].sum = 0;
        if ( rs(x) ) Tree[rs(x)].tag = 1, Tree[rs(x)].val = Tree[rs(x)].sum = 0;
    } 
}

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

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, n + 1, n + m) Tree[i].val = Tree[i].sum = 1;
    REP(i, 1, m) 
    { 
        scanf("%d%d", &a[i].u, &a[i].v);
        if ( a[i].u > a[i].v ) swap(a[i].u, a[i].v);
        id[a[i].u * n + a[i].v] = i;
    }
    int M = m;
    while ( 1 ) 
    { 
        scanf("%d", &a[++ m].opt);
        if ( a[m].opt == -1 ) { -- m; break ; }
        scanf("%d%d", &a[m].u, &a[m].v); 
        if ( a[m].u > a[m].v ) swap(a[m].u, a[m].v);
        if ( a[m].opt == 0 ) Map[a[m].u * n + a[m].v] = true;
    }
    REP(i, 1, M) 
    { 
        if ( Map[a[i].u * n + a[i].v] == true ) continue ;
        MakeRoot(a[i].u);
        if ( FindRoot(a[i].v) != a[i].u ) { Link(a[i].u, i + n); Link(i + n, a[i].v); continue ; }
        Split(a[i].u, a[i].v); Tree[a[i].v].tag = 1; Tree[a[i].v].sum = Tree[a[i].v].val = 0;
    }
    for ( int i = m; i > M; -- i )
    {
        if ( a[i].opt == 0 ) 
        {
            MakeRoot(a[i].u); 
            if ( FindRoot(a[i].v) != a[i].u ) 
            { 
                int x = id[a[i].u * n + a[i].v];
                Link(a[i].u, x); Link(x, a[i].v);
                continue ;
            }
            Split(a[i].u, a[i].v); Tree[a[i].v].tag = 1; Tree[a[i].v].sum = Tree[a[i].v].val = 0;
        }
        else
        {
            Split(a[i].u, a[i].v); ans[++ sum] = Tree[a[i].v].sum;
        }
    }
    for ( int i = sum; i >= 1; -- i ) printf("%d\n", ans[i]);
    return 0;
}
