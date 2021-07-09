/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2019年10月30日 星期三 15时02分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define x first
#define y second
#define pii pair<int, int>
typedef long long LL;

const int maxn = 600010;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, ret;
int dis[maxn], anc[maxn][20], deg[maxn];
multiset<int> d[maxn], Edge[maxn];
multiset<pii> Set;
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; anc[v][0] = u;
        DFS(v, u);
    }
}

inline int LCA(int x, int y) 
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int j = 19; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
    if ( x == y ) return x;
    for ( int j = 19; j >= 0; -- j ) if ( anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; }
    return anc[x][0];
}

inline void Modify(int pos, int val, bool opt)
{
    d[deg[pos]].erase(pos); deg[pos] += val; if ( opt ) d[deg[pos]].insert(pos);
}

inline void Del(int x)
{
    vector<int> p; p.clear();
    for ( multiset<int> :: iterator i = d[1].begin(); i != d[1].end(); )
    {
        if ( *i == x ) { ++ i; continue ; }
        vis[*i] = false; -- ret; Set.erase(pii(dis[*i], *i));
        for ( auto j : Edge[*i] ) 
        {
            Edge[j].erase(*i); Modify(j, -1, false);
            if ( deg[j] != 1 ) d[deg[j]].insert(j);
            else p.push_back(j);
        }
        Edge[*i].clear(); 
        multiset<int> :: iterator it = i; ++ i;
        Modify(*it, -1, true);
    }
    for ( auto i : p ) d[1].insert(i);
}

inline bool Check(int x, int y)
{
    if ( dis[x] >= dis[y] || LCA(x, y) != x ) return true;
    return false;
}

inline void Solve(int x)
{
    int Root = Set.begin() -> y, pre = 0, nex, t;
    if ( !vis[x] && Check(Root, x) ) pre = Root, nex = anc[Root][0];
    else if ( !vis[x] ) 
        for ( auto i : d[1] ) if ( dis[t = LCA(i, x)] > dis[pre] ) 
        {
            pre = t; nex = x;
            for ( int j = 19; j >= 0; -- j ) if ( dis[anc[nex][j]] > dis[pre] ) nex = anc[nex][j];
        }
    if ( pre ) 
    {
        ++ ret; vis[nex] = true; Set.insert(pii(dis[nex], nex));
        Modify(pre, 1, true); Modify(nex, 1, true); 
        Edge[nex].insert(pre); Edge[pre].insert(nex);
    }
    Del(pre ? nex : x);
}

int main()
{
    freopen("Slowset.in", "r", stdin);
    freopen("Slowset.out", "w", stdout);
    scanf("%d%d", &n, &m); ret = n;
    REP(i, 1, n - 1) 
    { 
        int u, v; scanf("%d%d", &u, &v); 
        add(u, v); add(v, u); ++ deg[u]; ++ deg[v]; 
        Edge[u].insert(v); Edge[v].insert(u);
    }
    dis[1] = 1; DFS(1, 0); 
    REP(j, 1, 19) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    REP(i, 1, n) { vis[i] = true; d[deg[i]].insert(i); Set.insert(pii(dis[i], i)); }
    REP(i, 1, m) { int x; scanf("%d", &x); Solve(x); }
    printf("%d\n", (int)Set.size());
    return 0;
}
