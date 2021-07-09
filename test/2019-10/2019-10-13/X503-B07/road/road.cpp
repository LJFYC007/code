/***************************************************************
	File name: road.cpp
	Author: ljfcnyali
	Create time: 2019年010月13日 星期日 09时07分23秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;
#define pii pair<LL, int>

const int maxn = 25000010;
const LL INF = 1e18;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, m, k, s, t; 
LL dis[600010], ans = INF;
bool vis[600010];

inline void add(int u, int v, int w) 
{
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
}

signed main()
{
    freopen("road.in", "r", stdin);
    freopen("road.out", "w", stdout);
    scanf("%d%d%d%d%d", &n, &m, &k, &s, &t);
    ++ k;
    REP(i, 1, m)
    {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        REP(o, 1, k)
        {
            int x = (o - 1) * n + u, y = (o - 1) * n + v, val = w;
            REP(j, o, k)
            {
                int X = (j - 1) * n + u, Y = (j - 1) * n + v;
                add(x, Y, val); add(y, X, val);
                val /= 2;
            }
        }
    }
    REP(i, 0, 600000) dis[i] = INF; dis[s] = 0;
    priority_queue<pii> Q; Q.push(make_pair(0, s));
    while ( !Q.empty() ) 
    {
        int u = Q.top().second; Q.pop();
        if ( vis[u] ) continue ; vis[u] = true;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i];
            if ( dis[v] > dis[u] + W[i] ) 
            {
                dis[v] = dis[u] + W[i];
                if ( !vis[v] ) Q.push(make_pair(-dis[v], v));
            }
        }
    }
    REP(i, 1, k) ans = min(ans, dis[(i - 1) * n + t]);
    if ( ans == INF ) { puts("NO"); return 0; }
    printf("%lld\n", ans);
    return 0;
}
