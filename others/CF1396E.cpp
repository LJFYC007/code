/***************************************************************
	File name: CF1396E.cpp
	Author: ljfcnyali
	Create time: 2020年09月18日 星期五 20时29分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, k, Root, Begin[maxn], Next[maxn], To[maxn], e, dis[maxn], size[maxn], num[maxn];
int MaxAns, MinAns, f[maxn];
set<int> Edge[maxn];
set<pii> a[maxn];
vector<int> b[maxn];
priority_queue<pii> Q;
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    size[u] = 1; int Max = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS1(v, u); size[u] += size[v]; Max = max(Max, size[v]);
    }
    Max = max(Max, n - size[u] - 1);
    if ( Max < n / 2 ) Root = u;
}

inline void DFS2(int u, int fa)
{
    size[u] = 1; 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        f[v] = u;
        dis[v] = dis[u] + 1; DFS2(v, u); size[u] += size[v];
        Edge[u].insert(v);
        MaxAns += size[v]; MinAns += size[v] % 2;
    }
}

inline void DFS3(int u, int t)
{
    if ( Edge[u].size() ) a[t].insert(pii(dis[u], u));
    for ( auto v : Edge[u] ) DFS3(v, t);
}

inline void DFS4(int u, int fa, int t)
{
    if ( !vis[u] ) b[t].push_back(u);
    for ( int i = Begin[u]; i; i = Next[i] ) if ( To[i] != fa ) DFS4(To[i], u, t);
}

inline void Check(int x, int t)
{
    if ( !Edge[x].size() ) a[t].erase(pii(dis[x], x));
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &k);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    DFS1(1, 0); DFS2(Root, 0);
    if ( k < MinAns || k > MaxAns || (MaxAns - k) % 2 != 0 ) { puts("NO"); return 0; }
    for ( auto v : Edge[Root] ) { DFS3(v, v); Q.push(pii(size[v], v)); }
    k = (MaxAns - k) / 2; puts("YES");
    while ( k ) 
    {
        int u = Q.top().second; Q.pop(); size[u] -= 2;
        int v = (*(-- a[u].end())).second;
        while ( dis[v] > k ) 
        {
            a[u].erase(-- a[u].end());
            v = (*(-- a[u].end())).second;
        }
        if ( Edge[v].size() >= 2 ) 
        {
            int s = *Edge[v].begin(); Edge[v].erase(s);
            int t = *Edge[v].begin(); Edge[v].erase(t);
            vis[s] = vis[t] = true; printf("%d %d\n", s, t); 
            Check(v, u);
        }
        else
        {
            int s = *Edge[v].begin(); Edge[v].erase(s);
            vis[s] = vis[v] = true; printf("%d %d\n", s, v);
            Edge[f[v]].erase(v); a[u].erase(pii(dis[v], v)); Check(f[v], u);
        }
        k -= dis[v]; if ( size[u] ) Q.push(pii(size[u], u));
    }

    for ( int i = Begin[Root]; i; i = Next[i] ) DFS4(To[i], Root, To[i]);

    while ( 1 ) 
    {
        int u = Q.top().second; Q.pop(); -- size[u];
        if ( Q.empty() ) { printf("%d %d\n", b[u].back(), Root); return 0; }
        int v = Q.top().second; Q.pop(); -- size[v];

        printf("%d %d\n", b[u].back(), b[v].back());        
        b[u].pop_back(); b[v].pop_back();

        if ( size[u] ) Q.push(pii(size[u], u));
        if ( size[v] ) Q.push(pii(size[v], v));
    }
    return 0;
}
