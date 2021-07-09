/***************************************************************
	File name: accompany.cpp
	Author: ljfcnyali
	Create time: 2020年07月18日 星期六 08时45分58秒
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

const int maxn = 4e5 + 10;
const int N = 1e9;
const int INF = 1e18;

int Mid, op, n, L, R, Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
map<int, pii> Map;
pii f[maxn][2];

inline pii max(pii a, pii b) { return a.x > b.x || (a.x == b.x && a.y > b.y) ? a : b; }
pii operator + (pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void DFS(int u, int fa)
{
    f[u][0] = pii(0, 0); f[u][1] = pii(-INF, -INF);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u);
        f[u][1] = max(f[u][1] + max(f[v][0], f[v][1]), f[u][0] + f[v][0] + pii(W[i] - Mid, 1));
        f[u][0] = f[u][0] + max(f[v][0], f[v][1]);
    }
}

inline int Solve(int x)
{
    int l = -N, r = N, ans = -1;
    while ( l <= r ) 
    {
        Mid = l + r >> 1; pii sum;
        if ( Map.count(Mid) ) sum = Map[Mid];
        else { DFS(1, 0); sum = max(f[1][0], f[1][1]); Map[Mid] = sum; }
        if ( sum.y >= x ) { ans = sum.x + x * Mid; l = Mid + 1; }
        else r = Mid - 1;
    }
    return ans;
}

signed main()
{
    freopen("accompany.in", "r", stdin);
    freopen("accompany.out", "w", stdout);
    scanf("%lld", &op);
    scanf("%lld%lld%lld", &n, &L, &R);
    REP(i, 2, n) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); add(v, u, w); }
    REP(i, L, R) { int x = Solve(i); if ( x == -1 ) printf("- "); else printf("%lld ", x); }
    puts("");
    return 0;
}
