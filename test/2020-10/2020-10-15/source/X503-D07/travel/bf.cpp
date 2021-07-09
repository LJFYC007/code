/***************************************************************
	File name: travel.cpp
	Author: ljfcnyali
	Create time: 2020年10月15日 星期四 10时30分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, q, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], ans;
map<int, bool> Map[11], Vis;

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void DFS(int u, int val)
{
    if ( Map[u].count(val) ) return ; Map[u][val] = true;
    if ( !Vis.count(val) ) { ++ ans; Vis[val] = true; }
    for ( int i = Begin[u]; i; i = Next[i] ) 
        DFS(To[i], val ^ W[i]);
}

signed main()
{
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &q);
    REP(i, 1, m) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); add(v, u, w); }
    DFS(1, 0);
    printf("%lld\n", ans);
    return 0;
}
