/***************************************************************
	File name: okfly.cpp
	Author: ljfcnyali
	Create time: 2020年09月06日 星期日 08时42分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 1e6 + 10;
const int INF = 1e9;

int T, n, m, Begin[maxn], Next[maxn], To[maxn], W[maxn], e;
int f[maxn], num[maxn][21], size[maxn], dis[maxn], p[maxn], anc[maxn];
struct node { int u, v, w; node(int a = 0, int b = 0, int c = 0) { u = a; v = b; w = c; } } Edge[maxn];
bool vis[maxn];
vector<int> pp;

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }

inline int get(int x, int y, int op)
{
    if ( op == 0 ) return size[x] - num[x][y];
    return num[x][y];
}

inline void Find(int x, int y, int num)
{
    if ( dis[x] <= dis[y] ) return ;
    int Min = INF, pos = 0;
    pp.clear(); pp.push_back(num); 
    if ( W[num] < Min ) { Min = W[num]; pos = num; } 
    while ( x != y ) 
    {
        pp.push_back(p[x]);
        if ( W[p[x]] < Min ) { Min = W[p[x]]; pos = p[x]; }
        x = anc[x];
    }
    vis[pos] = vis[pos ^ 1] = true;
    for ( auto i : pp ) if ( i != pos ) { W[i] += Min; W[i ^ 1] += Min; }
}

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        if ( !dis[v] ) 
        { 
            dis[v] = dis[u] + 1; p[v] = i; 
            anc[v] = u; DFS(v, u); 
        }
        else Find(u, v, i);
    }
}

signed main()
{
    freopen("okfly.in", "r", stdin);
    freopen("okfly.out", "w", stdout);
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d", &n, &m);
        e = 1; mem(Begin); mem(dis); mem(vis);
        REP(i, 1, m) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); }
        dis[1] = 1; DFS(1, 0); m = 0;
        REP(u, 1, n) for ( int i = Begin[u]; i; i = Next[i] ) 
            if ( u <= To[i] && !vis[i] ) Edge[++ m] = node(u, To[i], W[i]);

        sort(Edge + 1, Edge + m + 1, [](node &a, node &b) { return a.w < b.w; });
        REP(i, 1, n) 
        { 
            f[i] = i; size[i] = 1;
            for ( int j = 0; j <= 20; ++ j ) num[i][j] = (i >> j) & 1; 
        }
        LL ans = 0;
        for ( int i = m; i >= 1; -- i ) 
        {
            int x = find(Edge[i].u), y = find(Edge[i].v);
            REP(j, 0, 20)
            {
                int c = (Edge[i].w >> j) & 1;
                if ( c == 0 ) 
                {
                    ans += (1ll << j) * get(x, j, 0) * get(y, j, 1);
                    ans += (1ll << j) * get(x, j, 1) * get(y, j, 0);
                }
                else
                {
                    ans += (1ll << j) * get(x, j, 1) * get(y, j, 1);
                    ans += (1ll << j) * get(x, j, 0) * get(y, j, 0);
                }
                num[x][j] += num[y][j];
            }
            f[y] = x; size[x] += size[y];
        }
        printf("%lld\n", ans);
    }
    return 0;
}
