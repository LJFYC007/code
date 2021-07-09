/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年06月05日 星期五 08时16分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 1e8 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, a[maxn], w[maxn], f[maxn], dis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; 
        dis[v] = dis[u] + 1; f[v] = u; 
        DFS(v);
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, n) scanf("%lld", &w[i]);
    a[n + 1] = INF;
    for ( int i = n; i >= 1; -- i ) REP(j, i + 1, n + 1) if ( a[j] > a[i] ) { add(j, i); break ; }
    DFS(n + 1);
    REP(o, 1, m) 
    {
        int op, x, y; scanf("%lld%lld%lld", &op, &x, &y);
        if ( op == 1 ) 
        {
            w[x] += y;
            for ( int i = Begin[x]; i; i = Next[i] ) 
                w[To[i]] += y;
        }
        else 
        {
            int ans = w[x] + w[y]; 
            int u = x, v = y;
            if ( dis[u] < dis[v] ) swap(u, v);
            while ( dis[u] > dis[v] ) { u = f[u]; ans += w[u]; }
            if ( u == v ) ans -= w[u];
            while ( f[u] != f[v] ) { u = f[u]; v = f[v]; ans += w[u] + w[v]; }
            u = f[u]; ans += w[u];
            
            if ( u == x || u == y ) { u = f[u]; ans += w[u]; } 
        
            if ( u == n + 1 ) puts("?");
            else printf("%lld\n", ans);
        }
    }
    return 0;
}
