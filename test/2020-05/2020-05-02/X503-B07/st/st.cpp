/***************************************************************
	File name: st.cpp
	Author: ljfcnyali
	Create time: 2020年05月02日 星期六 08时36分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define ls(x) Tree[x].son[0]
#define rs(x) Tree[x].son[1]
#define fa(x) Tree[x].fa
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 998244353;

struct type
{
    int a, b;
    type(int x = 0, int y = 0) { a = x; b = y; }
} p1, p2;
type operator + (const type x, const type y) { return type((x.a + y.a) % Mod, (x.b + y.b) % Mod); }
type operator - (const type x, const type y) { return type((x.a - y.a) % Mod, (x.b - y.b) % Mod); }
type operator * (const type x, const type y) { return type((x.a * y.a + 5 * x.b * y.b) % Mod, (x.a * y.b + x.b * y.a) % Mod); }
type operator + (const type x, const int y) { return type((x.a + y) % Mod, x.b); }
type operator - (const type x, const int y) { return type((x.a - y) % Mod, x.b); }
type operator * (const type x, const int y) { return type(x.a * y % Mod, x.b * y % Mod); }

inline int power1(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline type power2(type a, int b) { type r = type(1, 0); while ( b ) { if ( b & 1 ) r = r * a; a = a * a; b >>= 1; } return r; }

inline type Inv(type x) { return type(x.a, -x.b) * power1((x.a * x.a - 5 * x.b * x.b) % Mod, Mod - 2); }

struct node 
{ 
    type pre, suf, prd, ans; 
    node(){};
    node (type val, int k = 1) 
    { 
        type x = Inv(val - 1);
        prd = power2(val, k);
        pre = suf = (prd * val - val) * x;
        ans = (pre - k) * val * x;
    }
} ;
node operator * (const node a, const node b) 
{
    node c;
    c.pre = a.pre + b.pre * a.prd;
    c.suf = b.suf + a.suf * b.prd;
    c.prd = a.prd * b.prd;
    c.ans = a.ans + b.ans + a.suf * b.pre;
    return c;
}
struct node1
{
    int son[2], tag, fa, size;
    type lazy1, lazy2, val1, val2;
    bool vis;
    node w1, w2;
} Tree[maxn];
int n, m, f[maxn];

inline bool IsRoot(int x) { return (ls(fa(x)) == x || rs(fa(x)) == x) ? false : true; }

inline void Update(int x) 
{ 
    Tree[x].tag ^= 1; 
    swap(Tree[x].w1.pre, Tree[x].w1.suf); 
    swap(Tree[x].w2.pre, Tree[x].w2.suf); 
    swap(ls(x), rs(x)); 
}

inline void PushTag(int root, type x, type y)
{
    Tree[root].vis = true; 
    Tree[root].lazy1 = Tree[root].val1 = x; Tree[root].lazy2 = Tree[root].val2 = y;
    Tree[root].w1 = node(x, Tree[root].size);
    Tree[root].w2 = node(y, Tree[root].size);
}

inline void PushUp(int root)
{
    Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size + 1;
    
    Tree[root].w1 = node(Tree[root].val1);
    Tree[root].w2 = node(Tree[root].val2);
    if ( ls(root) ) 
    {
        Tree[root].w1 = Tree[ls(root)].w1 * Tree[root].w1;
        Tree[root].w2 = Tree[ls(root)].w2 * Tree[root].w2;
    }
    if ( rs(root) ) 
    {
        Tree[root].w1 = Tree[root].w1 * Tree[rs(root)].w1;
        Tree[root].w2 = Tree[root].w2 * Tree[rs(root)].w2;
    }
}

inline void PushDown(int root)
{
    if ( Tree[root].tag ) 
    {
        Tree[root].tag ^= 1;
        if ( ls(root) ) Update(ls(root));
        if ( rs(root) ) Update(rs(root));
    }
    
    if ( Tree[root].vis ) 
    {
        Tree[root].vis = false;
        if ( ls(root) ) PushTag(ls(root), Tree[root].lazy1, Tree[root].lazy2);
        if ( rs(root) ) PushTag(rs(root), Tree[root].lazy1, Tree[root].lazy2);
    }
}

inline void Rotate(int x)
{
    int y = fa(x), z = fa(y), k = rs(y) == x, w = Tree[x].son[!k];
    if ( !IsRoot(y) ) Tree[z].son[rs(z) == y] = x;
    fa(x) = z; fa(y) = x;
    if ( w ) fa(w) = y;
    Tree[y].son[k] = w; Tree[x].son[!k] = y;
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

inline void MakeRoot(int root) { Access(root); Splay(root); Update(root); }

inline int FindRoot(int x) { Access(x); Splay(x); while ( ls(x) ) x = ls(x); Splay(x); return x; }

inline void Link(int u, int v) { MakeRoot(u); if ( FindRoot(v) == u ) return ; fa(u) = v; }

inline void Cut(int u, int v) { MakeRoot(u); if ( FindRoot(v) != u || fa(v) != u || ls(v) ) return ; fa(v) = rs(u) = 0; }

inline void Split(int u, int v) { MakeRoot(u); Access(v); Splay(v); }

signed main()
{
    freopen("st.in", "r", stdin);
    freopen("st.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    p1 = type(1, 1) * power1(2, Mod - 2); p2 = type(1, -1) * power1(2, Mod - 2);
    REP(i, 1, n) { int x; scanf("%lld", &x); PushUp(i); PushTag(i, power2(p1, x), power2(p2, x)); }
    REP(i, 2, n) { scanf("%lld", &f[i]); Link(i, f[i]); }
    while ( m -- ) 
    {
        int op, u, v, x;
        scanf("%lld", &op);
        if ( op == 1 ) { scanf("%lld%lld", &u, &v); Cut(u, f[u]); f[u] = v; Link(u, f[u]); }
        if ( op == 2 ) 
        { 
            scanf("%lld%lld%lld", &u, &v, &x); Split(u, v); 
            PushTag(v, power2(p1, x), power2(p2, x));
        }
        if ( op == 3 ) 
        {
            scanf("%lld", &u); Splay(u);
            type ans = Tree[u].val1 - Tree[u].val2;
            int ret = ans.a / sqrt(5) + ans.b;
            printf("%lld\n", (ret + Mod) % Mod);
        }
        if ( op == 4 ) 
        {
            scanf("%lld%lld", &u, &v); Split(u, v);
            type ans = Tree[v].w1.ans - Tree[v].w2.ans;
            int ret = ans.a / sqrt(5) + ans.b;
            printf("%lld\n", (ret + Mod) % Mod);
        }
    }
    return 0;
}
