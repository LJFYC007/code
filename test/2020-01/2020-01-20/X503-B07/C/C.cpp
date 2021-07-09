/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年01月20日 星期一 10时39分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 310;
const int INF = 1e18;

int n, m, sum1[maxn], sum2[maxn], ans = INF, dis[maxn], Begin[maxn], Next[maxn], To[maxn], e;
struct node 
{ 
    int R, B, EdgeR, EdgeB, fa; 
    node(int r = 0, int b = 0, int e1 = 0, int e2 = 0) { R = r; B = b; EdgeR = e1; EdgeB = e2; }
} Edge[maxn];
struct Node { int u, v, R, B; } Q[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline int Solve()
{
    REP(i, 2, n) if ( sum1[i] > Edge[i].R || sum2[i] > Edge[i].B ) return INF;
    int ret = 0;
    REP(i, 2, n) 
    {
        ret += sum1[i] * Edge[i].EdgeR;
        ret += sum2[i] * Edge[i].EdgeB;
    }
    return ret;
}

inline void DFS(int x, int sum)
{
    if ( x == m + 1 ) { ans = min(ans, sum + Solve()); return ; }
    int s = Q[x].u, t = Q[x].v;
    if ( s == t ) { DFS(x + 1, sum + Q[x].R); DFS(x + 1, sum + Q[x].B); }
    while ( Edge[t].fa != s ) { ++ sum1[t]; t = Edge[t].fa; }
    ++ sum1[t];
    DFS(x + 1, sum + Q[x].R);
    t = Q[x].v;
    while ( Edge[t].fa != s ) { -- sum1[t]; ++ sum2[t]; t = Edge[t].fa; }
    -- sum1[t]; ++ sum2[t];
    DFS(x + 1, sum + Q[x].B);
    t = Q[x].v;
    while ( Edge[t].fa != s ) { -- sum2[t]; t = Edge[t].fa; }
    -- sum2[t];
}

inline int Solve1()
{
    REP(i, 1, m) scanf("%lld%lld%lld%lld", &Q[i].u, &Q[i].v, &Q[i].R, &Q[i].B);
    DFS(1, 0);
    printf("%lld\n", ans == INF ? -1 : ans);
    return 0;
}

inline void DFS1(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; dis[v] = dis[u] + 1;
        DFS1(v);
    }
}

signed main()
{
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 2, n) 
    {
        scanf("%lld%lld%lld%lld%lld", &Edge[i].fa, &Edge[i].R, &Edge[i].B, &Edge[i].EdgeR, &Edge[i].EdgeB);
        add(Edge[i].fa, i); 
    }
    if ( m <= 18 ) return Solve1();
    ans = 0;
    DFS1(1);
    REP(i, 1, m)
    {
        scanf("%lld%lld%lld%lld", &Q[i].u, &Q[i].v, &Q[i].R, &Q[i].B);
        int s = Q[i].u, t = Q[i].v, sum1 = Q[i].R, sum2 = Q[i].B;
        if ( s != t ) 
        {
            while ( Edge[t].fa != s ) 
            {
                sum1 += Edge[t].EdgeR;
                sum2 += Edge[t].EdgeB;
                t = Edge[t].fa;
            }
            sum1 += Edge[t].EdgeR;
            sum2 += Edge[t].EdgeB;
        }
        ans += min(sum1, sum2);
    }
    printf("%lld\n", ans);
    return 0;
}
