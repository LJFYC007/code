/***************************************************************
	File name: CF1019E.cpp
	Author: ljfcnyali
	Create time: 2020年10月28日 星期三 16时50分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;
const int INF = 0x3f3f3f3f;

int n, m, N, Begin[maxn], Next[maxn], To[maxn], e = 1, U, V;
int size[maxn], S, cnt, ans[maxn], Min, A[maxn], B[maxn];
pii W[maxn], dis[maxn], val;
struct node 
{ 
    int v, k, b; 
    node ( int x = 0, int y = 0, int z = 0 ) { v = x; k = y; b = z; }
} a[maxn];
vector<node> Edge[maxn];
vector<int> g1, g2;
bool vis[maxn];

inline pii operator + (pii a, pii b) { return pii(a.first + b.first, a.second + b.second); }

inline void add(int u, int v, pii w)
{
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
    swap(u, v); To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
}

inline void Build(int l, int r, int u)
{
    if ( l == r ) { add(u, a[l].v, pii(a[l].k, a[l].b)); return ; }
    else { add(u, ++ N, pii(0, 0)); u = N; }
    int Mid = l + r >> 1; Build(l, Mid, u); Build(Mid + 1, r, u);
}

inline void DFS1(int u, int fa)
{
    int x = 0;
    for ( auto it : Edge[u] ) if ( it.v != fa ) a[++ x] = it;
    if ( x ) Build(1, x, u);
    for ( auto it : Edge[u] ) if ( it.v != fa ) DFS1(it.v, u);
}

inline void DFS2(int u, int fa)
{
    size[u] = 1 ;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || vis[i] ) continue ;
        DFS2(v, u); size[u] += size[v];
        int x = abs(S - size[v] - size[v]);
        if ( x < Min ) { Min = x; U = u; V = v; val = W[i]; cnt = i; }
    }
    // cout << size[u] << " ";
}

inline void DFS3(int u, int fa, int op)
{
    size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || vis[i] ) continue ;
        dis[v] = dis[u] + W[i];
        DFS3(v, u, op); size[u] += size[v];
    }
    if ( size[u] == 1 && op == 1 ) g1.push_back(u);
    if ( size[u] == 1 && op == 2 ) g2.push_back(u);
}

inline void Solve(int x, int y)
{
    g1.clear(); g2.clear();
    dis[x] = dis[y] = pii(0, 0); DFS3(x, y, 1); DFS3(y, x, 2);

    REP(i, 0, m - 1) A[i] = B[i] = 0;
    REP(i, 0, m - 1) for ( auto it : g1 ) A[i] = max(A[i], dis[it].first * i + dis[it].second);
    REP(i, 0, m - 1) for ( auto it : g2 ) B[i] = max(B[i], dis[it].first * i + dis[it].second);
    REP(i, 0, m - 1) ans[i] = max(ans[i], A[i] + B[i] + W[cnt].first * i + W[cnt].second);

    vis[cnt] = vis[cnt ^ 1] = true;
    S = size[x]; Min = INF; DFS2(x, y); if ( Min < INF ) Solve(U, V);
    S = size[y]; Min = INF; DFS2(y, x); if ( Min < INF ) Solve(U, V);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n - 1) 
    {
        int u, v, k, b; scanf("%lld%lld%lld%lld", &u, &v, &k, &b);
        Edge[u].push_back(node(v, k, b));
        Edge[v].push_back(node(u, k, b));
    }
    N = n; DFS1(1, 0);
    S = N; Min = INF; DFS2(1, 0); if ( Min < INF ) Solve(U, V);
    REP(i, 0, m - 1) printf("%lld ", ans[i]); puts("");
    return 0;
}
