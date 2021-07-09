/***************************************************************
	File name: P5304.cpp
	Author: ljfcnyali
	Create time: 2019年08月12日 星期一 21时39分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 2000010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, m, s, t, T, k, p[maxn], dis[maxn], ans;
bool vis[maxn];

struct node
{
    int u, v, w;
} a[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void Dijkstra(int s, int t)
{
    priority_queue< pair<int, int> > Q; Q.push(make_pair(0, s));
    memset(dis, 0x3f, sizeof(dis)); dis[s] = 0; mem(vis);
    while ( !Q.empty() ) 
    {
        int u = Q.top().second; Q.pop();
        // cerr << u << " ";
        if ( vis[u] ) continue ;
        vis[u] = true;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; 
            if ( dis[v] > dis[u] + W[i] ) 
            {
                dis[v] = dis[u] + W[i];
                if ( !vis[v] ) Q.push(make_pair(-dis[v], v));
            }
        }
    }
    // cerr << endl;
    // REP(i, 1, t) cerr << dis[i] << " "; cerr << endl;
    // cerr << dis[t] << endl;
    ans = min(ans, dis[t]);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d%d", &n, &m, &k);
        REP(i, 1, m) scanf("%d%d%d", &a[i].u, &a[i].v, &a[i].w);
        REP(i, 1, k) scanf("%d", &p[i]);
        s = n + 1; t = s + 1;
        ans = 0x3f3f3f3f;
        REP(j, 0, 20)
        {
            bool flag1 = false, flag2 = false;
            mem(Begin); e = 0;
            REP(i, 1, k)
                if ( p[i] & (1 << j) ) 
                {
                    add(s, p[i], 0);
                    flag1 = true;
                }
                else 
                {
                    add(p[i], t, 0);
                    flag2 = true;
                }
            if ( !flag1 || !flag2 ) continue ;
            REP(i, 1, m) add(a[i].u, a[i].v, a[i].w);
            Dijkstra(s, t);

            mem(Begin); e = 0;
            REP(i, 1, k)
                if ( !(p[i] & (1 << j)) ) 
                    add(s, p[i], 0);
                else 
                    add(p[i], t, 0);
            REP(i, 1, m) add(a[i].u, a[i].v, a[i].w);
            Dijkstra(s, t);
        }
        printf("%d\n", ans);
    }
    return 0;
}
