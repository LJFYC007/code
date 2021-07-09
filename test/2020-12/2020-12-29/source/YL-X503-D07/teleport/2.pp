/***************************************************************
	File name: teleport.cpp
	Author: ljfcnyali
	Create time: 2020年12月29日 星期二 10时24分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 210;
const int INF = 1e18;

int n, k, son[maxn], Begin[maxn], Next[maxn], To[maxn], e, W[maxn], fa[maxn];
int dis[maxn], f[maxn][maxn], g[maxn][maxn][maxn], h[maxn][maxn], anc[maxn], tot;

inline void add(int u, int v, int w) { fa[v] = u; To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; } 

inline void DFS(int u)
{
    f[u][0] = INF; anc[++ tot] = u;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; dis[v] = dis[u] + W[i]; DFS(v);
        REP(j, 1, k) f[u][j] += min(dis[v] - dis[u] + f[v][j - 1], g[v][j - 1][u]);
        REP(j, 0, k) REP(pos, 1, tot) 
            g[u][j][anc[pos]] += min(f[v][j] + dis[v] - dis[anc[pos]], g[v][j][anc[pos]]);
    }

    if ( son[u] > 1 ) 
    {
        REP(j, 0, k) for ( int x = Begin[u]; x; x = Next[x] )
        {
            int v1 = To[x], sum = 0;
            for ( int y = Begin[u]; y; y = Next[y] ) 
            {
                int v = To[y]; 
                if ( v == v1 ) sum += min(f[v][j] + dis[v] - dis[u], h[v][j]);
                else sum += min(f[v][j] + dis[v] - dis[fa[u]], g[v][j][fa[u]]);
            }
            h[u][j] = min(h[u][j], sum);
        }
        REP(j, 1, k)
        {
            int sum = 0;
            for ( int x = Begin[u]; x; x = Next[x] )
            {
                int v1 = To[x], sum = 0;
                for ( int y = Begin[u]; y; y = Next[y] ) 
                {
                    int v = To[y]; 
                    if ( v == v1 ) sum += f[v][j] + dis[v] - dis[u];
                    else sum += min(dis[v] - dis[u] + f[v][j - 1], g[v][j - 1][u]);
                }
                f[u][j] = min(f[u][j], sum);
            }
        }
    }

    if ( son[u] == 0 ) 
    {
        REP(j, 0, k) REP(pos, 1, tot) g[u][j][anc[pos]] = dis[u] - dis[anc[pos]];
        REP(j, 0, k) h[u][j] = dis[u] - dis[fa[u]];
    }
    -- tot;

    // cout << u << " " ; REP(i, 1, k) cout << f[u][i] << " "; cout << endl;
}

signed main()
{
    freopen("teleport.in", "r", stdin);
    freopen("teleport.out", "w", stdout);
    scanf("%lld%lld", &n, &k); ++ k;
    REP(i, 2, n) { int f, w; scanf("%lld%lld", &f, &w); add(f, i, w); ++ son[f]; }
    REP(i, 1, n) REP(j, 0, k) h[i][j] = INF;
    DFS(1); 
    if ( son[1] == 1 ) REP(i, 2, k) printf("%lld\n", f[1][i]);
    else REP(i, 1, k - 1) printf("%lld\n", f[1][i]);

    puts("");
    int ans = 0;
    REP(i, 1, n) if ( son[i] == 0 ) ans += dis[i] - dis[1];
    cout << ans << endl;
    int Max = 0; REP(i, 1, n) Max = max(Max, dis[i] - dis[1]);
    cout << ans - Max << endl;
    return 0;
}
