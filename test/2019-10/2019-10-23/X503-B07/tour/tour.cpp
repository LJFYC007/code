// luogu-judger-enable-o2
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
#define int long long
typedef long long LL;

const int maxn = 300010;
const int INF = 2147483647;

struct node
{
    int son[2], Min, id, lazy, fa;
} Tree[maxn];

struct Node
{
    int u, v, w;
    bool operator < (const Node &x) const { return w < x.w; }
} Edge[maxn];

int n, m, w[maxn], X, Y, s, t;
long double ans = INF; 

inline bool IsRoot(int x) { return (ls(fa(x)) == x || rs(fa(x)) == x) ? false : true; }

inline void PushUp(int x) 
{ 
    Tree[x].Min = w[x]; Tree[x].id = x;
    if ( ls(x) && Tree[ls(x)].Min < Tree[x].Min ) { Tree[x].Min = Tree[ls(x)].Min; Tree[x].id = Tree[ls(x)].id; }
    if ( rs(x) && Tree[rs(x)].Min < Tree[x].Min ) { Tree[x].Min = Tree[rs(x)].Min; Tree[x].id = Tree[rs(x)].id; }
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

signed main()
{
    freopen("tour.in", "r", stdin);
    freopen("tour.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, m) scanf("%lld%lld%lld", &Edge[i].u, &Edge[i].v, &Edge[i].w);
    scanf("%lld%lld", &s, &t);
    REP(i, 1, n) w[i] = INF;
    sort(Edge + 1, Edge + m + 1);
    REP(i, 1, m)
    {
        w[i + n] = Edge[i].w; 
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
            if ( Tree[Edge[i].v].Min >= Edge[i].w ) continue ;
            Splay(x); fa(ls(x)) = fa(rs(x)) = 0;
            Link(Edge[i].u, i + n); Link(i + n, Edge[i].v);
        }
        if ( Check(s, t) ) 
        { 
            Split(s, t); 
            if ( Edge[i].w * 1.0 / Tree[s].Min < ans ) 
            {
                ans = Edge[i].w * 1.0 / Tree[s].Min;
                X = Edge[i].w; Y = Tree[s].Min;
            }
        }
    }
    int p = __gcd(X, Y);
    if ( Y / p == 1 ) { printf("%lld\n", X / p); return 0; }
    printf("%lld/%lld\n", X / p, Y / p);
    return 0;
}
