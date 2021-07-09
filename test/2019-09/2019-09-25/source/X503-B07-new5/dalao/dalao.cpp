/***************************************************************
	File name: dalao.cpp
	Author: ljfcnyali
	Create time: 2019年09月25日 星期三 14时32分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxm = 40010;
const int maxn = 610;
const int INF = 0x7f7f7f7f;

int n, m, p, k, Begin[maxm], Next[maxm], To[maxm], e;
int T[maxm], W[maxm], a[maxn], dis[maxn][maxm], ans = 0x7f7f7f7f;
bool vis[maxn][maxm];
struct node
{
    int pos, w;
} p1, p2;

inline void add(int u, int v, int t, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; T[e] = t; W[e] = w; }

signed main()
{
    freopen("dalao.in", "r", stdin);
    freopen("dalao.out", "w", stdout);
    scanf("%lld%lld%lld%lld", &n, &m, &p, &k);
    REP(i, 1, k)
    {
        int x, num; scanf("%lld%lld", &x, &num);
        REP(j, 1, num) { int y; scanf("%lld", &y); a[x] |= 1 << y; }
    }
    REP(i, 1, m)
    {
        int x = 0, u, v, w, num; scanf("%lld%lld%lld%lld", &u, &v, &w, &num);
        REP(j, 1, num) { int y; scanf("%lld", &y); x |= 1 << y; }
        add(u, v, w, x); add(v, u, w, x);
    }
    queue<node> Q; p1.pos = 1; p1.w = a[1]; Q.push(p1);
    memset(dis, 0x7f, sizeof(dis)); dis[p1.pos][p1.w] = 0;
    while ( !Q.empty() ) 
    {
        p1 = Q.front(); Q.pop();
        // if ( p1.pos == n ) { ans = min(ans, dis[p1.pos][p1.w]); continue ; }
        for ( int i = Begin[p1.pos]; i; i = Next[i] ) 
        {
            int v = To[i];
            if ( (p1.w | W[i]) != p1.w ) continue ;
            p2.pos = v; p2.w = p1.w | a[p2.pos];
            if ( dis[p2.pos][p2.w] > dis[p1.pos][p1.w] + T[i] ) 
            {
                dis[p2.pos][p2.w] = dis[p1.pos][p1.w] + T[i];
                // if ( dis[p2.pos][p2.w] >= ans ) continue ;
                if ( !vis[p2.pos][p2.w] ) { vis[p2.pos][p2.w] = true; Q.push(p2); }
            }
        }
        vis[p1.pos][p1.w] = false;
    }
    REP(i, 0, 1 << (p + 1)) ans = min(ans, dis[n][i]);
    printf("%lld\n", ans == INF ? -1 : ans);
    return 0;
}
