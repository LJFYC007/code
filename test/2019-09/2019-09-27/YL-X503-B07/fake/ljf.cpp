/***************************************************************
	File name: fake.cpp
	Author: ljfcnyali
	Create time: 2019年09月27日 星期五 19时30分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 600010;
const int INF = 0x3f3f3f3f;
    
int Begin[maxn], Next[maxn], To[maxn], e, n, m, sum[maxn];
int ans, f[maxn], dis[maxn], dep[maxn], c[maxn], tot, Root[maxn];
vector<int> a[maxn];
struct node
{
    int l, r, val, t;
} Tree[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dep[v] = dep[u] + 1;
        DFS1(v, u);
    }
}

inline int cha(int x) { return x == f[x] ? x : cha(f[x]); }

inline int Merge(int x, int y)
{
    if ( !x || ! y ) return x + y;
    if ( Tree[x].val > Tree[y].val || (Tree[x].val == Tree[y].val && x > y) ) swap(x, y);
    Tree[x].r = Merge(Tree[x].r, y);
    f[Tree[x].r] = x;
    if ( dis[Tree[x].l] < dis[Tree[x].r] ) swap(Tree[x].l, Tree[x].r); 
    dis[x] = dis[Tree[x].r] + 1;
    return x;
}

inline int DFS2(int u, int fa)
{
    if ( !Root[u] ) { Root[u] = ++ tot; Tree[Root[u]].val = INF; }
    int size = 0;
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; if ( v == fa ) continue ;
        size += DFS2(v, u);
        int x = cha(Root[u]), y = cha(Root[v]);
        Merge(x, y);
    }
    // cerr << "pos = " << u << " ";
    for ( auto i : a[u] ) 
    {
        // cerr << i << " ";
        Tree[++ tot].val = dep[i]; Tree[tot].t = i;
        Merge(cha(Root[u]), tot);
        ++ size;
    }
    // cerr << "size = " << size << " c = " << c[u] << endl;
    // cerr << "Min = " << Tree[cha(Root[u])].t << " Min_Val = " << Tree[cha(Root[u])].val << endl;
    while ( size > c[u] ) 
    {
        -- size; -- ans;
        int fx = cha(Root[u]);              
        -- sum[Tree[fx].t];
        // cerr << Tree[fx].t << endl;
        Tree[fx].val = INF;
        f[Tree[fx].l] = Tree[fx].l; f[Tree[fx].r] = Tree[fx].r;
        f[fx] = Merge(Tree[fx].l, Tree[fx].r);
    }
    size -= sum[u];
    return size;
}

int main()
{
    freopen("fake.in", "r", stdin);
    freopen("fake1.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &c[i]);
    REP(i, 1, maxn - 10) f[i] = i;
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    dep[1] = 1; DFS1(1, 0);
    ans = m;
    REP(i, 1, m)
    {
        int u, v; scanf("%d%d", &u, &v);
        if ( dep[u] > dep[v] ) swap(u, v);
        a[v].push_back(u);
        ++ sum[u];
    }
    DFS2(1, 0);
    printf("%d\n", ans);
    return 0;
}
