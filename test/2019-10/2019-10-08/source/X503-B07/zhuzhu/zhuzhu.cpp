/***************************************************************
	File name: zhuzhu.cpp
	Author: ljfcnyali
	Create time: 2019年10月08日 星期二 20时56分23秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define int long long
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1000010;
const int Mod = 1e9 + 7;

int T, n, m, X, fa[maxn], val[maxn], tot, dis[maxn], sum1, sum2, sum3;
int Begin[maxn], Next[maxn], To[maxn], e, anc[maxn][30];
struct node
{
    int u, v, w;
    bool operator < (const node &a) const { return w < a.w; }
} a[maxn];

inline int power(int a, int b)
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = (r * a) % Mod; a = (a * a) % Mod; b >>= 1; }
    return r;
}

inline int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i];
        dis[v] = dis[u] + 1; anc[v][0] = u;
        DFS(v);
    }
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int j = 23; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
    if ( x == y ) return x;
    for ( int j = 23; j >= 0; -- j ) if ( anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; }
    return anc[x][0];
}

signed main()
{
    freopen("zhuzhu.in", "r", stdin);
    freopen("zhuzhu.out", "w", stdout);
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld%lld", &n, &m, &X);
        mem(Begin); e = 0; mem(anc); mem(dis); mem(val);
        REP(i, 1, m) scanf("%lld%lld%lld", &a[i].u, &a[i].v, &a[i].w);
        sort(a + 1, a + m + 1); 
        tot = n; REP(i, 1, 2 * n) fa[i] = i; 
        int sum = 0, ans = 0;
        REP(i, 1, m)
        {
            int fx = find(a[i].u), fy = find(a[i].v);
            if ( fx == fy ) continue ;
            ++ tot; val[tot] = a[i].w;
            add(tot, fx); add(tot, fy);
            fa[fx] = fa[fy] = tot;
            sum += a[i].w;
        }
        if ( sum > X ) { puts("0"); continue ; }
        sum1 = sum2 = sum3 = 0;
        dis[tot] = 1; DFS(tot);
        REP(j, 1, 23) REP(i, 1, tot) anc[i][j] = anc[anc[i][j - 1]][j - 1];
        REP(i, 1, m)
        {
            int x = val[LCA(a[i].u, a[i].v)];
            if ( sum - x + a[i].w < X ) ++ sum1;
            else if ( sum - x + a[i].w == X ) ++ sum2;
            else ++ sum3;
        }
        if ( sum < X ) ans = power(2, sum3 + 1) * (power(2, sum2) - 1) % Mod;
        else ans = power(2, sum3) * (power(2, sum2) - 2) % Mod;
        printf("%lld\n", ans);
    }
    return 0;
}
