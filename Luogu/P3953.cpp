/***************************************************************
	File name: P3953.cpp
	Author: ljfcnyali
	Create time: 2019年07月07日 星期日 21时05分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 400010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, m, k, Mod, dis[maxn], f[maxn][51], p[maxn], sum;
bool vis[maxn];

struct node
{
    int pos, dis, id;
} a[maxn];

inline void add(int u, int v, int w)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
    W[e] = w;
}

inline int cmp(node a, node b)
{
    return a.dis < b.dis || (a.dis == b.dis && a.id < b.id);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    while ( T -- ) 
    {
        mem(Begin); memset(dis, 0x3f, sizeof(dis)); mem(f); mem(p); mem(vis); e = sum = 0;
        scanf("%d%d%d%d", &n, &m, &k, &Mod);
        REP(i, 1, m)
        {
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            add(u, v, w);
        }
        queue<int> Q; Q.push(1); vis[1] = true; dis[1] = 0;
        bool flag = false;
        while ( !Q.empty() ) 
        {
            int u = Q.front(); Q.pop();
            ++ sum;
            if ( sum >= 2000000 ) { flag = true; printf("-1\n"); break ; }
            for ( int i = Begin[u]; i; i = Next[i] ) 
            {
                int v = To[i];
                if ( dis[v] >= dis[u] + W[i] ) 
                {
                    dis[v] = dis[u] + W[i];
                    if ( p[v] <= p[u] ) p[v] = p[u] + 1;
                    if ( !vis[v] ) 
                    {
                        vis[v] = true; Q.push(v);
                    }
                }
            }
            vis[u] = false;
        }
        if ( flag == true ) continue ;
        REP(i, 1, n) { a[i].pos = i; a[i].dis = dis[i]; a[i].id = p[i]; }
        sort(a + 1, a + n + 1, cmp);
        f[1][0] = 1;
        REP(o, 0, k)
        {
            REP(i, 1, n)
            {
                int u = a[i].pos; if ( dis[u] == 0x3f3f3f3f ) continue ;
                for ( int i = Begin[u]; i; i = Next[i] ) 
                {
                    int v = To[i];
                    if ( dis[u] + W[i] + o <= dis[v] + k ) 
                    {
                        f[v][dis[u] + W[i] + o - dis[v]] += f[u][o];
                        f[v][dis[u] + W[i] + o - dis[v]] %= Mod;
                    }
                }
            }
        }
        int ans = 0;
        REP(i, 0, k) ans = (ans + f[n][i]) % Mod;
        printf("%d\n", ans);
    }
    return 0;
}
