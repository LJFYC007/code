/***************************************************************
	File name: starway.cpp
	Author: ljfcnyali
	Create time: 2020年10月03日 星期六 08时32分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 1e5 + 10;
const double INF = 1e18;

int n, m, k, s, t, Begin[maxn], Next[maxn], To[maxn], e, belong[maxn];
double W[maxn], dis[maxn];
pii a[maxn];
bool vis[maxn];

inline void add(int u, int v, double w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline double Dis(pii a, pii b) { return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }

inline void DFS(int u, int fa, double ans)
{
    if ( u == t ) { printf("%.7lf\n", ans / 2); return ; }
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u, max(ans, W[i]));
    }
}

signed main()
{
    freopen("starway.in", "r", stdin);
    freopen("starway.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &k);
    REP(i, 1, k) scanf("%lld%lld", &a[i].x, &a[i].y);
    s = k + 1; t = k + 2;
    vis[s] = true; dis[t] = m; belong[t] = s;
    REP(i, 1, k) { dis[i] = a[i].y; belong[i] = s; }
    REP(o, 2, k + 2)
    {
        double Min = INF; int pos = 0;
        REP(i, 1, k + 2) if ( !vis[i] && dis[i] < Min ) { Min = dis[i]; pos = i; }
        vis[pos] = true; add(belong[pos], pos, Min); add(pos, belong[pos], Min);
        
        if ( pos == t ) 
        {
            REP(i, 1, k) if ( dis[i] > m - a[i].y ) { dis[i] = m - a[i].y; belong[i] = pos; }
        }
        else 
        {
            REP(i, 1, k) if ( dis[i] > Dis(a[pos], a[i]) ) { dis[i] = Dis(a[pos], a[i]); belong[i] = pos; }
            if ( dis[t] > m - a[pos].y ) { dis[t] = m - a[pos].y; belong[t] = pos; }
        }
    }
    DFS(s, 0, 0);
    return 0;
}
