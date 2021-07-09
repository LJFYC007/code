/***************************************************************
	File name: P4234.cpp
	Author: ljfcnyali
	Create time: 2019年08月18日 星期日 11时02分49秒
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

const int maxn = 5000010;

struct node
{
    int son[2], Min, id, fa, lazy;
} Tree[maxn];

int n, m, w[maxn], num, Min, ans = 0x3f3f3f3f;
bool vis[maxn];

struct Node
{
    int u, v, w;
    bool operator < (const Node &a) const { return w < a.w; } 
} a[maxn];

inline bool IsRoot(int x) { return (ls(fa(x)) == x || rs(fa(x)) == x) ? false : true; }

inline void PushUp(int x)
{
    Tree[x].Min = w[x]; Tree[x].id = x;
    if ( ls(x) && Tree[ls(x)].Min < Tree[x].Min ) { Tree[x].Min = Tree[ls(x)].Min; Tree[x].id = Tree[ls(x)].id; }
    if ( rs(x) && Tree[rs(x)].Min < Tree[x].Min ) { Tree[x].Min = Tree[rs(x)].Min; Tree[x].id = Tree[rs(x)].id; }
}

inline void Update(int x) { Tree[x].lazy ^= 1; swap(ls(x), rs(x)); }

inline void PushDown(int x)
{
    if ( !Tree[x].lazy ) return ;
    if ( ls(x) ) Update(ls(x));
    if ( rs(x) ) Update(rs(x));
    Tree[x].lazy = 0;
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

inline void Cut(int u, int v) { MakeRoot(u); if ( FindRoot(v) != u || fa(v) != u || ls(v) ) return ; fa(v) = rs(u) = 0; }

inline void Split(int u, int v) { MakeRoot(u); Access(v); Splay(v); }

inline bool Check(int u, int v) { MakeRoot(u); return FindRoot(v) == u; }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, m) scanf("%d%d%d", &a[i].u, &a[i].v, &a[i].w);
    sort(a + 1, a + m + 1);
    REP(i, 1, n) w[i] = 0x3f3f3f3f; REP(i, n + 1, n + m) w[i] = a[i - n].w;
    REP(i, 1, m)
    {
        if ( a[i].u == a[i].v ) continue ;
        if ( !Check(a[i].u, a[i].v) ) 
        {
            Link(a[i].u, i + n); 
            Link(i + n, a[i].v);
            ++ num; vis[i] = true;
        }
        else
        {
            Split(a[i].u, a[i].v);
            int x = Tree[a[i].v].id; Splay(x); fa(ls(x)) = fa(rs(x)) = 0;
            vis[x - n] = false;
            Link(a[i].u, i + n); Link(i + n, a[i].v);
            vis[i] = true;
        }
        if ( num == n - 1 ) 
        {
            while ( !vis[Min] ) ++ Min;
            ans = min(ans, a[i].w - a[Min].w); 
        }
    }
    printf("%d\n", ans);
    return 0;
}
