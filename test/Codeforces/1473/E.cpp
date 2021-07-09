/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2021年01月15日 星期五 08时34分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 4e6 + 10;
const int INF = 1e18;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], dis[maxn];
bool vis[maxn];
queue<int> Q;
struct node { int u, v, w; } Edge[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, m) 
    {
        scanf("%lld%lld%lld", &Edge[i].u, &Edge[i].v, &Edge[i].w);
        add(Edge[i].u, Edge[i].v + n, 0);
        add(Edge[i].u, Edge[i].v + n + n, Edge[i].w * 2);
        add(Edge[i].u, Edge[i].v + n + n + n, Edge[i].w);
        add(Edge[i].u + n, Edge[i].v + n + n + n, Edge[i].w * 2);
        add(Edge[i].u + n + n, Edge[i].v + n + n + n, 0);
        swap(Edge[i].u, Edge[i].v);
        add(Edge[i].u, Edge[i].v + n, 0);
        add(Edge[i].u, Edge[i].v + n + n, Edge[i].w * 2);
        add(Edge[i].u, Edge[i].v + n + n + n, Edge[i].w);
        add(Edge[i].u + n, Edge[i].v + n + n + n, Edge[i].w * 2);
        add(Edge[i].u + n + n, Edge[i].v + n + n + n, 0);
    }
    REP(i, 1, 4) REP(j, 1, m) 
    {
        add(Edge[j].u + (i - 1) * n, Edge[j].v + (i - 1) * n, Edge[j].w);
        add(Edge[j].v + (i - 1) * n, Edge[j].u + (i - 1) * n, Edge[j].w);
    }
    REP(i, 2, n * 4) dis[i] = INF; vis[1] = true; Q.push(1);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
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
    REP(i, 2, n) printf("%lld ", dis[i + n + n + n]); puts("");
    return 0;
}
