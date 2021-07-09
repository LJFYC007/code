/***************************************************************
	File name: P3320.cpp
	Author: ljfcnyali
	Create time: 2019年08月08日 星期四 20时56分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 200010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int anc[maxn][20], n, m, dis[maxn], ans, dfn[maxn], cnt, H[maxn];
bool vis[maxn];

struct node
{
    int val, pos;
    bool operator < (const node &a) const { return val < a.val; }
} p1, p2;
set<node> Set;

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; anc[v][0] = u; H[v] = H[u] + W[i];
        DFS(v, u);
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

inline int Dis(int x, int y) { return H[x] + H[y] - 2 * H[LCA(x, y)]; }

inline void DFS1(int u, int fa)
{
    dfn[u] = ++ cnt;
    for ( int i = Begin[u]; i; i = Next[i] ) if ( To[i] != fa ) DFS1(To[i], u);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n - 1) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); add(v, u, w); }
    dis[1] = 1; DFS(1, 0);
    REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    DFS1(1, 0);
    REP(i, 1, m)
    {
        int x, nxt, pre; scanf("%lld", &x);
        p1.val = dfn[x]; p1.pos = x;
        if ( !vis[x] ) 
        {
            vis[x] = true;
            Set.insert(p1);
            if ( Set.size() == 1 ) goto end;
            set<node>::iterator it = Set.find(p1);
            if ( it == Set.begin() ) pre = (*(-- Set.end())).pos;
            else pre = (*(-- it)).pos, ++ it;
            if ( it == -- Set.end() ) nxt = (*Set.begin()).pos;
            else nxt = (*(++ it)).pos, -- it;
            ans = ans - Dis(nxt, pre) + Dis(nxt, x) + Dis(x, pre);
        }
        else
        {
            vis[x] = false;
            if ( Set.size() < 2 ) { Set.erase(p1); ans = 0; goto end ; }
            auto it = Set.find(p1);
            if ( it == Set.begin() ) pre = (*(-- Set.end())).pos;
            else pre = (*(-- it)).pos, ++ it;
            if ( it == -- Set.end() ) nxt = (*Set.begin()).pos;
            else nxt = (*(++ it)).pos, -- it;
            ans = ans - Dis(nxt, x) - Dis(x, pre) + Dis(nxt, pre);
            Set.erase(p1);
        }
end: ;
        printf("%lld\n", ans);
    }
    return 0;
}
