/***************************************************************
	File name: P4115.cpp
	Author: ljfcnyali
	Create time: 2021年01月08日 星期五 15时32分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define fa(x) Tree[x].fa
#define ls(x) Tree[x].son[0]
#define rs(x) Tree[x].son[1]
typedef long long LL;

const int maxn = 1e6 + 10;
const int INF = 1e9;

int n, m, tot, Stack[maxn], Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
char s[10]; bool Col[maxn];
struct node { int son[2], fa, tag, ans, len, lMax, rMax, sum; multiset<int> Set1, Set2; } Tree[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; } 

inline int max(int a, int b, int c) { return max(a, max(b, c)); }
inline bool IsRoot(int x) { return ls(fa(x)) != x && rs(fa(x)) != x; }
inline void Insert(int x, int y) { Tree[x].Set1.insert(Tree[y].ans); Tree[x].Set2.insert(Tree[y].lMax); }
inline void Delete(int x, int y)
{
    // cerr << x << " " << y << " " << Tree[y].ans << endl;
    // for ( auto it : Tree[x].Set1 ) cerr << it << " "; cerr << endl;
    auto it = Tree[x].Set1.lower_bound(Tree[y].ans); Tree[x].Set1.erase(it);
    it = Tree[x].Set2.lower_bound(Tree[y].lMax); Tree[x].Set2.erase(it);
}
inline void PushUp(int root)
{
    Tree[root].sum = Tree[ls(root)].sum + Tree[rs(root)].sum + Tree[root].len;
    Tree[root].lMax = max(Tree[ls(root)].lMax, Tree[rs(root)].lMax + Tree[ls(root)].sum + Tree[root].len);
    Tree[root].lMax = max(Tree[root].lMax, *(-- Tree[root].Set2.end()) + Tree[ls(root)].sum + Tree[root].len);
    Tree[root].rMax = max(Tree[rs(root)].rMax, Tree[ls(root)].rMax + Tree[rs(root)].sum + Tree[root].len);
    Tree[root].rMax = max(Tree[root].rMax, *(-- Tree[root].Set2.end()) + Tree[rs(root)].sum + Tree[root].len);
    Tree[root].ans = max(Tree[ls(root)].ans, Tree[rs(root)].ans, *(-- Tree[root].Set1.end()));
    int Max = max(Tree[ls(root)].rMax, Tree[rs(root)].lMax), Maxx = min(Tree[ls(root)].rMax, Tree[rs(root)].lMax);
    auto it = -- Tree[root].Set2.end(); if ( *it > Max ) { Maxx = Max; Max = *it; } else Maxx = max(Maxx, *it);
    -- it; if ( *it > Max ) { Maxx = Max; Max = *it; } else Maxx = max(Maxx, *it); 
    Tree[root].ans = max(Tree[root].ans, Max + Maxx + Tree[root].len);
}
inline void PushTag(int root) { Tree[root].tag ^= 1; swap(ls(root), rs(root)); swap(Tree[root].lMax, Tree[root].rMax); }
inline void PushDown(int root) 
{ 
    if ( !Tree[root].tag ) return ; Tree[root].tag ^= 1;
    if ( ls(root) ) PushTag(ls(root)); if ( rs(root) ) PushTag(rs(root));
}
inline void Rotate(int x)
{
    int y = fa(x), z = fa(y), k = rs(y) == x, w = Tree[x].son[!k];
    if ( !IsRoot(y) ) Tree[z].son[rs(z) == y] = x;
    fa(x) = z; fa(y) = x; if ( w ) fa(w) = y;
    Tree[x].son[!k] = y; Tree[y].son[k] = w;
    PushUp(y); PushUp(x);
}
inline void Splay(int x)
{
    int y = x, z; Stack[tot = 1] = y;
    while ( !IsRoot(y) ) Stack[++ tot] = y = fa(y); while ( tot ) PushDown(Stack[tot --]);
    while ( !IsRoot(x) ) 
    {
        y = fa(x); z = fa(y);
        if ( !IsRoot(y) ) Rotate((ls(y) == x) ^ (ls(z) == y) ? x : y);
        Rotate(x);
    }
}
inline void Access(int root) 
{ 
    for ( int x = 0; root; x = root, root = fa(root) ) 
    { 
        // cerr << x << " " << root << endl;
        Splay(root); if ( rs(root) ) Insert(root, rs(root)); if ( x ) Delete(root, x);
        rs(root) = x; PushUp(root); 
    } 
}
inline void MakeRoot(int x) { Access(x); Splay(x); PushTag(x); }
inline void Link(int u, int v) { MakeRoot(u); MakeRoot(v); fa(u) = v; Insert(v, u); PushUp(v); }

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ; 
        DFS(v, u); int x = ++ m; Tree[x].len = Tree[x].sum = W[i];
        Access(v),Splay(v),Tree[v].fa = x; Insert(x, v); PushUp(x);
        Access(x),Splay(x),Tree[x].fa = u; Insert(u, x); PushUp(u);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n); Tree[0].ans = Tree[0].lMax = Tree[0].rMax = -INF;
    REP(i, 1, n + n - 1) 
    {
        Tree[i].ans = Tree[i].lMax = Tree[i].rMax = -INF; 
        Insert(i, 0); if ( i <= n ) Insert(i, n + n); else Insert(i, 0);
    }
    REP(i, 1, n - 1) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); }
    m = n; DFS(1, 0); scanf("%d", &m);
    int ans = Tree[1].ans;
    while ( m -- ) 
    {
        scanf("%s", s + 1);
        if ( s[1] == 'A' ) 
        { 
            if ( ans < 0 ) puts("They have disappeared.");
            else printf("%d\n", ans);
        }
        else 
        { 
            int x; scanf("%d", &x); Access(x); Splay(x); Col[x] ^= 1; 
            if ( Col[x] == 0 ) { Delete(x, 0); Insert(x, n + n); }
            else { Insert(x, 0); Delete(x, n + n); }
            PushUp(x); ans = Tree[x].ans;
        }
    }
    return 0;
}
