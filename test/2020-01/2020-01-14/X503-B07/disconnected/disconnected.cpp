/***************************************************************
	File name: disconnected.cpp
	Author: ljfcnyali
	Create time: 2020年01月14日 星期二 08时57分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, k, Begin[maxn], Next[maxn], To[maxn], e, dis[maxn], c[maxn], g[maxn][5];
int Root1[maxn], tot, anc[maxn][20], Root2[maxn], ans1[maxn], ans2[maxn];
set<pii> Edge[maxn];
vector<int> p, p2, t;
vector<pii> p1;
bool vis[maxn], use[maxn];
struct Node { int u, v; } a[maxn];
struct node { int lson, rson, sum; } Tree[maxn << 5];

inline void Modify(int &root, int l, int r, int pos)
{
    if ( !root ) root = ++ tot;
    ++ Tree[root].sum;
    if ( l == r ) return ;
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(ls(root), l, Mid, pos);
    else Modify(rs(root), Mid + 1, r, pos);
}

inline int Merge(int p, int q, int l, int r)
{
    if ( !p || !q ) return p + q;
    int root = ++ tot; Tree[root].sum = Tree[p].sum + Tree[q].sum;
    if ( l == r ) return root;
    int Mid = l + r >> 1;
    ls(root) = Merge(ls(p), ls(q), l, Mid);
    rs(root) = Merge(rs(p), rs(q), Mid + 1, r);
    return root;
}

inline int Query(int root, int l, int r, int pos)
{
    if ( !root ) return 0; 
    if ( l == r ) return Tree[root].sum;
    int Mid = l + r >> 1;
    if ( pos <= Mid ) return Query(ls(root), l, Mid, pos);
    else return Query(rs(root), Mid + 1, r, pos);
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa) 
{ 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    { 
        int v = To[i]; if ( v == fa ) continue ;
        auto it = Edge[u].lower_bound(pii(v, 0));
        if ( dis[v] ) 
        {
            Modify(Root1[u], 1, n, it -> second);
            continue ;
        }
        vis[it -> second] = true;
        dis[v] = dis[u] + 1; DFS(v, u);
    }
}

inline void DFS2(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ; 
        auto it = Edge[u].lower_bound(pii(v, 0));
        if ( !vis[it -> second] ) continue ;
        anc[v][0] = u;
        DFS2(v, u);
        Root1[u] = Merge(Root1[u], Root1[v], 1, n);
    }
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int j = 18; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
    if ( x == y ) return x;
    for ( int j = 18; j >= 0; -- j ) if ( anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; }
    return anc[x][0];
}

int main()
{
    freopen("disconnected.in", "r", stdin);
    freopen("disconnected.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, m) 
    { 
        scanf("%d%d", &a[i].u, &a[i].v); 
        Edge[a[i].u].insert(pii(a[i].v, i)); 
        Edge[a[i].v].insert(pii(a[i].u, i));
        add(a[i].u, a[i].v); add(a[i].v, a[i].u); 
    }
    dis[1] = 1; DFS(1, 0); DFS2(1, 0);
    REP(i, 1, m) 
    {
        if ( dis[a[i].u] > dis[a[i].v] ) swap(a[i].u, a[i].v);
        if ( !vis[i] ) t.push_back(i);
    }
    REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    scanf("%d", &k);
    REP(o, 1, k)
    {
        scanf("%d", &c[o]); p.clear(); p1.clear(); p2.clear();
        REP(i, 1, c[o]) 
        { 
            scanf("%d", &g[o][i]); int x = g[o][i];
            if ( !vis[x] ) { p2.push_back(x); use[x] = true; }
            else p.push_back(x);
        }
        for ( auto i : p ) 
        {
            p1.clear(); p1.push_back(pii(1, a[i].v));
            for ( auto j : p ) if ( a[j].v != a[i].v && LCA(a[j].v, a[i].v) == a[i].v ) p1.push_back(pii(-1, a[j].v));
            for ( auto j : t ) 
            {
                if ( use[j] ) continue ;
                int sum = 0;
                for ( auto k : p1 ) sum += k.first * Query(Root1[k.second], 1, n, j);
                if ( sum > 0 ) goto NEXT1;
            }
            ans1[o] = -1;
            goto NEXT2;
NEXT1 : ;
        }
        ans1[o] = 1;
NEXT2 : ;
        for ( auto i : p2 ) use[i] = false;
    }

    mem(dis); mem(Begin); e = tot = 0; mem(Root1); mem(vis); mem(use);
    REP(i, 1, n) for ( auto j : Edge[i] ) add(i, j.first);
    dis[1] = 1; DFS(1, 0); DFS2(1, 0);
    REP(i, 1, m) 
    {
        if ( dis[a[i].u] > dis[a[i].v] ) swap(a[i].u, a[i].v);
        if ( !vis[i] ) t.push_back(i);
    }
    REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    REP(o, 1, k)
    {
        p.clear(); p1.clear(); p2.clear();
        REP(i, 1, c[o]) 
        { 
            int x = g[o][i];
            if ( !vis[x] ) { p2.push_back(x); use[x] = true; }
            else p.push_back(x);
        }
        for ( auto i : p ) 
        {
            p1.clear(); p1.push_back(pii(1, a[i].v));
            for ( auto j : p ) if ( a[j].v != a[i].v && LCA(a[j].v, a[i].v) == a[i].v ) p1.push_back(pii(-1, a[j].v));
            for ( auto j : t ) 
            {
                if ( use[j] ) continue ;
                int sum = 0;
                for ( auto k : p1 ) sum += k.first * Query(Root1[k.second], 1, n, j);
                if ( sum > 0 ) goto NEXT3;
            }
            ans2[o] = -1;
            goto NEXT4;
NEXT3 : ;
        }
        ans2[o] = 1;
NEXT4 : ;
        for ( auto i : p2 ) use[i] = false;
    }
    REP(o, 1, 10) printf("%d ", ans1[o]); puts("");
    REP(o, 1, 10) printf("%d ", ans2[o]); puts("");
    REP(o, 1, k) if ( ans1[o] == -1 || ans2[o] == -1 ) puts("Disconnected"); else puts("Connected");
    return 0;
}
