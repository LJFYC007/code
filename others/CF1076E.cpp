/***************************************************************
	File name: CF1076E.cpp
	Author: ljfcnyali
	Create time: 2019年09月26日 星期四 20时48分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 600010;
const int INF = 0x3f3f3f3f;

int n, m, Begin[maxn], Next[maxn], To[maxn], e;
int ans[maxn], dis[maxn], a[maxn];
vector< pair<int, int> > p[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa, int sum)
{
    for ( auto i : p[u] ) 
    {
        a[dis[u]] += i.second;
        if ( i.first + dis[u] + 1 <= n ) 
            a[i.first + dis[u] + 1] -= i.second;
    }
    sum += a[dis[u]];
    ans[u] = sum;
    for ( int i = Begin[u]; i; i = Next[i] ) if ( To[i] != fa ) { dis[To[i]] = dis[u] + 1; DFS(To[i], u, sum); }
    for ( auto i : p[u] ) 
    {
        a[dis[u]] -= i.second;
        if ( i.first + dis[u] + 1 <= n ) 
            a[i.first + dis[u] + 1] += i.second;
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%I64d", &n);
    REP(i, 1, n - 1) { int u, v; scanf("%I64d%I64d", &u, &v); add(u, v); add(v, u); }
    scanf("%I64d", &m);
    REP(i, 1, m) { int v, d, x; scanf("%I64d%I64d%I64d", &v, &d, &x); p[v].push_back(make_pair(d, x)); }
    dis[1] = 1; DFS(1, 0, 0);
    REP(i, 1, n) printf("%I64d ", ans[i]); puts("");
    return 0;
}
