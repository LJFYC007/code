/***************************************************************
	File name: P1501.cpp
	Author: ljfcnyali
	Create time: 2019年08月16日 星期五 19时41分37秒
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

const int maxn = 100010;
const int Mod = 51061;

struct node
{
    int son[2], lazy, sum, add, mul, fa, val, size;
} Tree[maxn];

int n, m;

inline bool IsRoot(int x) { return (rs(fa(x)) == x || ls(fa(x)) == x) ? false : true; }

inline void PushUp(int x) 
{ 
    Tree[x].sum = (Tree[ls(x)].sum + Tree[rs(x)].sum + Tree[x].val) % Mod; 
    Tree[x].size = Tree[ls(x)].size + Tree[rs(x)].size + 1; 
}

inline void Update(int x) { Tree[x].lazy ^= 1; swap(ls(x), rs(x)); }

inline void PushTag(int x, int add, int mul)
{
    Tree[x].sum = (add * Tree[x].size + Tree[x].sum * mul) % Mod;
    Tree[x].add = (Tree[x].add * mul + add) % Mod;
    Tree[x].val = (Tree[x].val * mul + add) % Mod;
    Tree[x].mul = (Tree[x].mul * mul) % Mod;
}

inline void PushDown(int x)
{
    if ( Tree[x].lazy ) { Tree[x].lazy ^= 1; if ( ls(x) ) Update(ls(x)); if ( rs(x) ) Update(rs(x)); }
    if ( ls(x) ) PushTag(ls(x), Tree[x].add, Tree[x].mul);
    if ( rs(x) ) PushTag(rs(x), Tree[x].add, Tree[x].mul);
    Tree[x].add = 0; Tree[x].mul = 1;
}

inline void Rotate(int x)
{
    int y = fa(x), z = fa(y), k = rs(y) == x, w = Tree[x].son[!k];
    if ( !IsRoot(y) ) Tree[z].son[rs(z) == y] = x;
    fa(x) = z; fa(y) = x;
    if ( w ) fa(w) = y;
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

inline void Link(int u, int v) { MakeRoot(u); if ( FindRoot(v) == u ) return ; fa(u) = v; }

inline void Cut(int u, int v) { MakeRoot(u); if ( FindRoot(v) != u || fa(v) != u || ls(v) ) return ; fa(v) = rs(u) = 0; }

inline void Split(int u, int v) { MakeRoot(u); Access(v); Splay(v); }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) Tree[i].size = Tree[i].sum = Tree[i].val = Tree[i].mul = 1;
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); Link(u, v); }
    REP(i, 1, m)
    {
        char s[3]; scanf("%s", s);
        int u, v; scanf("%lld%lld", &u, &v);
        if ( s[0] == '-' ) 
        {
            Cut(u, v);
            scanf("%lld%lld", &u, &v);
            Link(u, v);
            continue ;
        }
        Split(u, v);
        if ( s[0] == '+' ) { int x; scanf("%lld", &x); PushTag(v, x, 1); }
        if ( s[0] == '*' ) { int x; scanf("%lld", &x); PushTag(v, 0, x); }
        if ( s[0] == '/' ) printf("%lld\n", Tree[v].sum), cerr << Tree[v].sum << endl;
    }
    return 0;
}
