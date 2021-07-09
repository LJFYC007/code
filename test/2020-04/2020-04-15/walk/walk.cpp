/***************************************************************
	File name: walk.cpp
	Author: ljfcnyali
	Create time: 2020年04月15日 星期三 19时48分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, ans[maxn], f[maxn], g[maxn], Begin[maxn], Next[maxn], To[maxn], e;
bool vis[maxn];
vector<int> p;
vector<pii> W[maxn];

inline void DFS(const int u, const int fa)
{
    vis[u] = true;
    int Max = -1, Maxx = -1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u);
        g[u] = max(g[u], g[v] + 1);
        f[u] = max(f[u], f[v]);
        if ( g[v] >= Max ) { Maxx = Max; Max = g[v]; }
        else if ( g[v] >= Maxx ) Maxx = g[v];
    }
    if ( Max != -1 && Maxx != -1 ) f[u] = max(f[u], Max + Maxx + 2);
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

int main()
{
    freopen("walk.in", "r", stdin);
    freopen("walk.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n - 1)
    {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        for ( int j = 1; j * j <= w; ++ j ) 
        {
            if ( w % j != 0 ) continue ;
            int x = j, y = w / j;
            W[x].push_back(pii(u, v));
            if ( x != y ) W[y].push_back(pii(u, v));
        }
    }
    for ( int i = maxn - 10; i >= 1; -- i )
    {
        if ( !W[i].size() ) continue ;
        p.clear(); e = 0;
        for ( auto j : W[i] ) 
        {
            int x = j.first, y = j.second;
            Begin[x] = Begin[y] = 0;
            vis[x] = vis[y] = false;
            p.push_back(x); p.push_back(y);
            f[x] = f[y] = g[x] = g[y] = 0;
        }
        for ( auto j : W[i] ) 
        {
            int x = j.first, y = j.second;
            add(x, y); add(y, x);
        }
        for ( auto j : p ) 
        {
            if ( vis[j] ) continue ;
            DFS(j, 0);
            int Max = max(f[j], g[j]);
            ans[Max] = max(ans[Max], i);
        }
    }
    for ( int i = n - 1; i >= 1; -- i ) ans[i] = max(ans[i], ans[i + 1]);
    REP(i, 1, n) printf("%d\n", ans[i]);
    return 0;
}
