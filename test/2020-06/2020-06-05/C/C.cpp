/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年06月05日 星期五 18时42分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e18;
const double eps = 1e-10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e = 1, S, T, dis[maxn];
double f[maxn], W[maxn];

inline void add(int u, int v, double w) 
{ 
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; 
    swap(u, v); w = 0;
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; 
}

inline bool BFS()
{
    queue<int> Q; Q.push(S);
    REP(i, 1, T) dis[i] = 0; dis[S] = 1;
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( dis[v] || W[i] < eps ) continue ;
            dis[v] = dis[u] + 1; Q.push(v);
            if ( v == T ) return true;
        }
    }
    return false;
}

inline double DFS(int u, int t, double flow)
{
    if ( u == t || flow < eps ) return flow;
    double x = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( dis[v] != dis[u] + 1 || W[i] < eps ) continue ;
        double val = DFS(v, t, min(flow, W[i]));
        if ( val < eps ) continue ;
        x += val; flow -= val;
        W[i] -= val; W[i ^ 1] += val;
    }
    return x;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, 10)
    {
        int x; scanf("%lld%lf", &x, &f[i]);
        f[i] = log(f[i]);
    }
    S = n * 10 + 1; T = S + 1;
    REP(i, 1, n)
    {
        double x;
        REP(j, 1, 10) { scanf("%lf", &x); x = log(x); add(S, (i - 1) * 10 + j, x); }
        REP(j, 1, 10) { scanf("%lf", &x); x = log(x); add((i - 1) * 10 + j, T, x); }
    }
    REP(i, 1, m)
    {
        int a, b, c; scanf("%lld%lld%lld", &a, &b, &c);
        add((a - 1) * 10 + c, (b - 1) * 10 + c, f[c]);
        add((b - 1) * 10 + c, (a - 1) * 10 + c, f[c]);
    }
    double ans = 0;
    while ( BFS() ) while ( double flow = DFS(S, T, INF) ) ans += flow;
    printf("%lf\n", exp(ans));
    return 0;
}
