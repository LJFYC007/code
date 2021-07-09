/***************************************************************
	File name: P6577.cpp
	Author: ljfcnyali
	Create time: 2020年07月21日 星期二 15时15分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 510;
const int INF = 1e18;

int n, m, a[maxn][maxn], slack[maxn], pre[maxn], px[maxn], py[maxn], vx[maxn], vy[maxn];
bool visx[maxn], visy[maxn];

inline void Find(int u)
{
    while ( u ) 
    {
        int t = px[pre[u]];
        px[pre[u]] = u;
        py[u] = pre[u];
        u = t;
    }
}

inline void BFS(int s)
{
    REP(i, 1, n) slack[i] = INF; mem(visx); mem(visy);
    queue<int> Q; Q.push(s);
    while ( 1 ) 
    {
        while ( !Q.empty() ) 
        {
            int u = Q.front(); Q.pop(); visx[u] = true;
            REP(i, 1, n) if ( !visy[i] && vx[u] + vy[i] - a[u][i] < slack[i] ) 
            {
                slack[i] = vx[u] + vy[i] - a[u][i];
                pre[i] = u; 
                if ( !slack[i] ) 
                {
                    visy[i] = true;
                    if ( !py[i] ) { Find(i); return ; }
                    else Q.push(py[i]);
                }
            }
        }
        int d = INF;
        REP(i, 1, n) if ( !visy[i] ) d = min(d, slack[i]);
        REP(i, 1, n)
        {
            if ( visx[i] ) vx[i] -= d;
            if ( visy[i] ) vy[i] += d; else slack[i] -= d;
        }
        REP(i, 1, n) if ( !visy[i] && !slack[i] ) 
        {
            visy[i] = true;
            if ( !py[i] ) { Find(i); return ; }
            else Q.push(py[i]);
        }
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) { REP(j, 1, n) a[i][j] = -INF; vx[i] = -INF; }
    REP(i, 1, m) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); a[u][v] = w; vx[u] = max(vx[u], w); }
    REP(i, 1, n) BFS(i);
    int ans = 0;
    REP(i, 1, n) ans += vx[i] + vy[i];
    printf("%lld\n", ans);
    REP(i, 1, n) printf("%lld ", py[i]); puts("");
    return 0;
}
