/***************************************************************
    File name: P4768.cpp
    Author: ljfcnyali
    Create time: 2019年07月12日 星期五 21时10分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define min minn

inline int minn(int a, int b) { return a < b ? a : b; }

const int maxn = 800010;

int Begin[maxn], Next[maxn], To[maxn], e, W1[maxn], W2[maxn];
int n, m, T, Q, K, S, dis[maxn], f[maxn], p[maxn], cnt, ans;
int son[maxn][2], val[maxn], num[maxn], anc[maxn][20], size[maxn];
bool use[maxn];

struct node
{
    int x, dis;
    node(int X = 0, int Dis = 0) { x = X; dis = Dis; }
    bool operator < (const node &a) const { return dis > a.dis; }
} p1, p2;

struct Node
{
    int u, v, w;
    bool operator < (const Node &a) const { return w > a.w; }
} Edge[maxn];

inline void add(int u, int v, int l, int a)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
    W1[e] = l; W2[e] = a;
}

inline void Dijkstra()
{
    priority_queue<node> Q; 
    dis[1] = 0; Q.push((node){1, 0});
    while ( !Q.empty() ) 
    {
        p1 = Q.top(); Q.pop();
        if ( use[p1.x] ) continue ;
        use[p1.x] = true;
        for ( int i = Begin[p1.x]; i; i = Next[i] ) 
        {
            int v = To[i];
            if ( use[v] ) continue ;
            if ( dis[v] > dis[p1.x] + W1[i] ) 
            {
                dis[v] = dis[p1.x] + W1[i];
                Q.push((node){v, dis[v]});
            }
        }
    }
}

inline int cha(int x) { return x == f[x] ? x : f[x] = cha(f[x]); }

inline int Solve(int u, int x)
{
    for ( register int j = 19; j >= 0; -- j ) if ( anc[u][j] && val[anc[u][j]] > x ) u = anc[u][j];
    while ( anc[u][0] && val[anc[u][0]] > x ) u = anc[u][0];
    return num[u];
}

inline void read(int &x)
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    read(T);
    while ( T -- )
    {
        mem(Begin); e = 0; memset(dis, 0x3f, sizeof(dis)); mem(use); mem(size);
        read(n); read(m);
        REP(i, 1, m) 
        { 
            int u, v, l, a; 
            read(u); read(v); read(l); read(a);
            add(u, v, l, a); add(v, u, l, a); 
            Edge[i].u = u; Edge[i].v = v; Edge[i].w = a;
        }
        Dijkstra();
        REP(i, 1, n) { f[i] = p[i] = i; num[i] = dis[i]; } cnt = n;
        sort(Edge + 1, Edge + m + 1);
        REP(i, 1, m)
        {
            int fx = cha(Edge[i].u), fy = cha(Edge[i].v);
            if ( fx == fy ) continue ;
            if ( size[fx] == size[fy] ) ++ size[fx];
            if ( size[fx] < size[fy] ) swap(fx, fy);
            f[fy] = fx; ++ cnt;
            son[cnt][0] = p[fx]; son[cnt][1] = p[fy];
            anc[p[fx]][0] = cnt; anc[p[fy]][0] = cnt;
            num[cnt] = min(num[p[fx]], num[p[fy]]);
            p[fx] = cnt; val[cnt] = Edge[i].w;
        }
        REP(j, 1, 19) REP(i, 1, cnt) anc[i][j] = anc[anc[i][j - 1]][j - 1];
        ans = 0;
        read(Q); read(K); read(S);
        while ( Q -- )
        {
            int u, x; read(u); read(x);
            u = (u + K * ans - 1) % n + 1;
            x = (x + K * ans) % (S + 1);
            printf("%d\n", ans = Solve(u, x));
        }
    }
    return 0;
}
