/***************************************************************
	File name: P4822.cpp
	Author: ljfcnyali
	Create time: 2019年07月15日 星期一 21时34分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 20000010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, m, k, dis[maxn], ans = 0x3f3f3f3f;
bool vis[maxn];

inline void add(int u, int v, int w) 
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
    W[e] = w;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &k);
    REP(i, 1, m)
    {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        add(u, v, w); add(v, u, w);
        REP(i, 1, k)
        {
            add(u + i * n, v + i * n, w);
            add(v + i * n, u + i * n, w);
            add(u + (i - 1) * n, v + i * n, w / 2);
            add(v + (i - 1) * n, u + i * n, w / 2);
        }
    }
    queue<int> Q; Q.push(1); memset(dis, 0x3f, sizeof(dis)); dis[1] = 0;
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
    REP(i, 1, k + 1) ans = min(ans, dis[n * i]);
    printf("%d\n", ans);
    return 0;
}
