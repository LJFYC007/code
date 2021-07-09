/***************************************************************
	File name: walk.cpp
	Author: ljfcnyali
	Create time: 2019年07月09日 星期二 08时50分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define swap Swap
typedef long long LL;

const int maxn = 500010;

LL Begin[maxn], Next[maxn], To[maxn], e, W[maxn]; 
LL anc[maxn][20], n, m, dis[maxn], a[maxn], t;

inline void Swap(LL &a, LL &b) { t = a; a = b; b = t; }

struct node
{
    LL u, v, w;
} p[maxn];

inline void add(LL u, LL v, LL w)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
    W[e] = w;
}

inline void DFS(LL u, LL fa)
{   
    for ( LL i = Begin[u]; i; i = Next[i] ) 
    {
        LL v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1;
        anc[v][0] = u;
        a[v] = W[i];
        DFS(v, u);
    }
}

inline LL LCA(LL x, LL y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( LL j = 17; j >= 0; -- j )
        if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
    if ( x == y ) return x;
    for ( LL j = 17; j >= 0; -- j )
        if ( anc[x][j] != anc[y][j] ) 
        {
            x = anc[x][j];
            y = anc[y][j];
        }
    return anc[x][0];
}

inline void read(LL &x)
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

int main()
{
    freopen("walk.in", "r", stdin);
    freopen("walk.out", "w", stdout);
    read(n); read(m);
    REP(i, 1, n - 1) 
    { 
        LL u, v, w; 
        read(u); read(v); read(w);
        add(u, v, w); add(v, u, w); 
        p[i].u = u; p[i].v = v; p[i].w = w;
    }
    dis[1] = 1; 
    DFS(1, 0);
    REP(j, 1, 17) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    while ( m -- ) 
    {
        LL opt; read(opt);
        if ( opt == 1 ) 
        {
            LL u, v, w; read(u); read(v); read(w);
            LL fa = LCA(u, v);
            while ( u != fa && v != fa ) 
            {
                if ( a[u] < a[v] ) swap(u, v);
                w /= a[u]; u = anc[u][0];
                if ( w == 0 ) break ;
            }
            if ( u == fa ) swap(u, v);
            while ( u != fa ) { w /= a[u]; u = anc[u][0]; if ( w == 0 ) break ; }
            printf("%lld\n", w);
        }
        else
        {
            LL x, w; read(x); read(w);
            if ( anc[p[x].v][0] == p[x].u ) swap(p[x].u, p[x].v);
            a[p[x].u] = w;
        }
    }
    return 0;
}
