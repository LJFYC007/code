/***************************************************************
	File name: P3238.cpp
	Author: ljfcnyali
	Create time: 2020年04月16日 星期四 16时07分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e5 + 10;
const int INF = 0x3f3f3f3f;

int n, m, k, dis[maxn], Begin[maxn], Next[maxn], To[maxn], e, W[maxn], a[maxn], f[maxn], p[maxn];
bool vis[maxn], use[maxn];
struct node { int u, v, w; } Edge[maxn];
queue<int> Q;
priority_queue<pii, vector<pii>, greater<pii> > ans;

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &k);
    REP(i, 1, m) scanf("%d%d%d", &Edge[i].u, &Edge[i].v, &Edge[i].w);
    memset(f, 0x3f, sizeof(f)); f[n] = 0;
    REP(i, 1, k) 
    { 
        scanf("%d", &a[i]); use[a[i]] = true;
        p[Edge[a[i]].u] = i; p[Edge[a[i]].v] = i + 1;
    }
    for ( int i = k; i >= 1; -- i ) f[Edge[a[i]].u] = f[Edge[a[i]].v] + Edge[a[i]].w; 
    REP(i, 1, m) 
    {
        if ( use[i] ) continue ;
        add(Edge[i].u, Edge[i].v, Edge[i].w);
    }
    memset(dis, 0x3f, sizeof(dis)); dis[1] = 0; vis[1] = true;
    REP(i, 1, k)
    {
        Q.push(Edge[a[i]].u); vis[Edge[a[i]].u] = true;
        while ( !Q.empty() ) 
        {
            int u = Q.front(); Q.pop();
            if ( p[u] > i ) ans.push(pii(dis[u] + f[u], p[u]));
            for ( int i = Begin[u]; i; i = Next[i] ) 
            {
                int v = To[i];
                if ( dis[v] > dis[u] + W[i] ) 
                {
                    dis[v] = dis[u] + W[i];
                    if ( !vis[v] ) { vis[v] = true; Q.push(v); }
                }
            }
            vis[u] = false;
        }
        while ( !ans.empty() && ans.top().second <= i ) ans.pop();
        if ( !ans.empty() ) printf("%d\n", ans.top().first);
        else puts("-1");
        add(Edge[a[i]].u, Edge[a[i]].v, Edge[a[i]].w);
        dis[Edge[a[i]].v] = dis[Edge[a[i]].u] + Edge[a[i]].w;
    }
    return 0;
}
