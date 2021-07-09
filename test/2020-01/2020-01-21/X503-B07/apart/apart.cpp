/***************************************************************
	File name: apart.cpp
	Author: ljfcnyali
	Create time: 2020年01月21日 星期二 08时31分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 8010;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int dis[maxn], ans;
bool vis[maxn];

inline void add(int u, int v, int w)
{
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
    swap(u, v);
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
}

int main()
{
    freopen("apart.in", "r", stdin);
    freopen("apart.out", "w", stdout);
    int T; scanf("%d", &T);
    while ( T -- ) 
    {
        ans = e = 0; mem(Begin);
        scanf("%d%d", &n, &m);
        if ( n <= 10 ) 
        {
            REP(i, 1, m) 
            { 
                int u, v, w; scanf("%d%d%d", &u, &v, &w); 
                ++ n; add(u, n, 1);
                REP(j, 3, w * 2) { add(n, n + 1, 1); ++ n; }
                add(n, v, 1);
            }
        }
        else 
        {
            REP(i, 1, m) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, n + i, w); add(n + i, v, w); }
            n += m;
        }
        REP(i, 1, n)   
        {
            priority_queue<pii, vector<pii>, greater<pii> > Q;
            memset(dis, 0x3f, sizeof(dis)); mem(vis);
            dis[i] = 0; Q.push(pii(0, i));
            while ( !Q.empty() ) 
            {
                int u = Q.top().second; Q.pop();
                if ( vis[u] ) continue ; vis[u] = true;
                for ( int i = Begin[u]; i; i = Next[i] ) 
                {
                    int v = To[i]; 
                    if ( dis[v] > dis[u] + W[i] ) 
                    {
                        dis[v] = dis[u] + W[i];
                        if ( !vis[v] ) Q.push(pii(dis[v], v));
                    }
                }
            }
            REP(j, 1, n) ans = max(ans, dis[j]);
        }
        printf("%.1lf\n", ans / 2.0);
    }
    return 0;
}
