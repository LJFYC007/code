/***************************************************************
	File name: P2939.cpp
	Author: ljfcnyali
	Create time: 2019年07月03日 星期三 17时01分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 20000010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, m, k, dis[maxn / 10];

struct node
{
    int x, dis;
    bool operator < (const node x) const
    {
        return dis > x.dis;
    }
} ;

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
        REP(j, 1, k)
        {
            add((j - 1) * n + u, j * n + v, 0); add((j - 1) * n + v, j * n + u, 0);
            add(j * n + u, j * n + v, w); add(j * n + v, j * n + u, w);
        }
    }
    priority_queue<node> Q; Q.push((node){1, 0}); memset(dis, 0x3f, sizeof(dis)); dis[1] = 0;
    while ( !Q.empty() ) 
    {
        node u = Q.top(); Q.pop();
        if ( dis[u.x] != u.dis ) continue ;
        for ( int i = Begin[u.x]; i; i = Next[i] ) 
        {
            int v = To[i];
            if ( dis[v] > dis[u.x] + W[i] ) 
            {
                dis[v] = dis[u.x] + W[i];
                Q.push((node){v, dis[v]});
            }
        }
    }
    int ans = 0x3f3f3f3f;
    REP(i, 1, k + 1) ans = min(ans, dis[i * n]);
    printf("%d\n", ans);
    return 0;
}
