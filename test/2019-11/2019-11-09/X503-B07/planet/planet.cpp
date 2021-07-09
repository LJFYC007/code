/***************************************************************
	File name: planet.cpp
	Author: ljfcnyali
	Create time: 2019年11月09日 星期六 09时15分46秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define piii pair<pii, pii>
#define x first
#define y second
#define int long long
typedef long long LL;

const int maxn = 600010;
const int INF = 1e18;

int n, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], dis[maxn], ans;
piii a[maxn];
bool vis[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

signed main()
{
    freopen("planet.in", "r", stdin);
    freopen("planet.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) { scanf("%lld%lld%lld", &a[i].x.x, &a[i].x.y, &a[i].y.x); a[i].y.y = i; }
    sort(a + 1, a + n + 1);
    REP(i, 2, n) { add(a[i - 1].y.y, a[i].y.y, a[i].x.x - a[i - 1].x.x); add(a[i].y.y, a[i - 1].y.y, a[i].x.x - a[i - 1].x.x); }
    sort(a + 1, a + n + 1, [](piii x, piii y) { return x.x.y < y.x.y; });
    REP(i, 2, n) { add(a[i - 1].y.y, a[i].y.y, a[i].x.y - a[i - 1].x.y); add(a[i].y.y, a[i - 1].y.y, a[i].x.y - a[i - 1].x.y); }
    sort(a + 1, a + n + 1, [](piii x, piii y) { return x.y.x < y.y.x; });
    REP(i, 2, n) { add(a[i - 1].y.y, a[i].y.y, a[i].y.x - a[i - 1].y.x); add(a[i].y.y, a[i - 1].y.y, a[i].y.x - a[i - 1].y.x); }
    priority_queue<pii, vector<pii>, greater<pii> > Q; Q.push(pii(0, 1));
    REP(i, 2, n) dis[i] = INF;
    while ( !Q.empty() ) 
    {
        int u = Q.top().y, x = Q.top().x; Q.pop();
        if ( vis[u] ) continue ; vis[u] = true; ans += x;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i];
            if ( dis[v] > W[i] ) { dis[v] = W[i]; Q.push(pii(dis[v], v)); }
        }
    }
    printf("%lld\n", ans);
    return 0;
}
