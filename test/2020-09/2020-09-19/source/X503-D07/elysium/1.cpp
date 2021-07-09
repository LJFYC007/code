/***************************************************************
	File name: elysium.cpp
	Author: ljfcnyali
	Create time: 2020年09月19日 星期六 08时26分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3010;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, num[maxn];
int a[maxn], ans, f[maxn][maxn], dis[maxn], g[maxn];
vector<pii> c[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u)
{
    REP(i, 0, dis[u] - 1) f[u][i] = a[u]; 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; dis[v] = dis[u] + 1; DFS(v);
        REP(j, 0, n) f[u][j] += f[v][j];
    }
    int N = n;
    if ( c[u].size() ) N = dis[u] + c[u].back().first;
    REP(i, 0, N) { g[i] = f[u][i]; f[u][i] -= num[u]; } 
    int sum = 0;
    for ( int i = (int)c[u].size() - 1; i >= 0; -- i ) 
    {
        REP(j, 0, dis[u] + c[u][i].first) f[u][j] = max(f[u][j], g[dis[u] + c[u][i].first] - sum);
        sum += c[u][i].second;
    }
}

signed main()
{
    freopen("elysium.in", "r", stdin);
    freopen("elysium.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 2, n) { int u; scanf("%lld", &u); add(u, i); }
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, m)
    {
        int x, d, v; scanf("%lld%lld%lld", &x, &d, &v);
        c[x].push_back(pii(d, v)); num[x] += v;
    }
    REP(i, 1, n) sort(c[i].begin(), c[i].end());
    dis[1] = 1; DFS(1);
    REP(i, 0, n) ans = max(ans, f[1][i]);
    printf("%lld\n", ans);
    return 0;
}
