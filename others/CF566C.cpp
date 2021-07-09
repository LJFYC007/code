/***************************************************************
	File name: CF566C.cpp
	Author: ljfcnyali
	Create time: 2021年01月25日 星期一 14时58分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 4e5 + 10;
const int INF = 9e18;

int n, a[maxn], Begin[maxn], Next[maxn], To[maxn], e, W[maxn], Root, Max, size[maxn], S, pos;
bool vis[maxn];
double ans = INF, f[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; } 

inline void Get(int u, int fa)
{
    size[u] = 1; int x = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || vis[v] ) continue ;
        Get(v, u); size[u] += size[v]; x = max(x, size[v]);
    }
    x = max(x, S - size[u]);
    if ( x < Max ) { Max = x; Root = u; } 
}

inline double calc(double x) { return sqrt(x * x * x); }

inline double DFS1(int u, int fa, int dep)
{
    double ret = calc(dep) * a[u];
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ; 
        ret += DFS1(v, u, dep + W[i]);
    }
    return ret;
}

inline double DFS2(int u, int fa, int dep)
{
    double ret = sqrt((double)dep) * a[u] * 1.5; 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ; 
        ret += DFS2(v, u, dep + W[i]);
    }
    return ret;
}

inline void Solve(int u)
{
    double t = DFS1(u, 0, 0); if ( t < ans ) { ans = t; pos = u; } 
    double sum = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i];  
        f[v] = DFS2(v, u, W[i]);
        sum += f[v];
    }
    vis[u] = true;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( vis[v] || sum - f[v] - f[v] > 0 ) continue ; 
        Max = S = size[v]; Get(v, 0); Solve(Root); return ; 
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n); REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, n - 1) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); add(v, u, w); } 
    Max = S = n; Get(1, 0); Solve(Root);
    printf("%lld %.6lf\n", pos, ans);
    return 0;
}
