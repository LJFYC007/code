/***************************************************************
	File name: CF936E.cpp
	Author: ljfcnyali
	Create time: 2020年10月25日 星期日 16时46分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 6e5 + 10;
const int INF = 0x3f3f3f3f;

int n, m, q, tot, Begin[maxn], Next[maxn], To[maxn], e, Root, belong[maxn];
int size[maxn], S, anc[maxn], *c[2][maxn], C[maxn * 10], *mem, Dis[maxn], l[maxn];
int dt[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
pii dis[20][300010];
struct node 
{ 
    int x, l, r; 
    node(int a = 0, int b = 0, int c = 0) { x = a; l = b; r = c; }
} a[maxn];
struct data
{
    int x, y, dis, pos;
    data(int a = 0, int b = 0, int c = 0, int d = 0) { x = a; y = b; dis = c; pos = d; }
} ;
vector<int> cell[maxn], Big[maxn];
map<int, int> Map[maxn];
bool vis[maxn];

inline int lowbit(int x) { return x & -x; }

inline void Modify(int op, int x, int pos, int val) 
{ 
    if ( pos <= 0 ) { cout << op << " " << x << " " << pos << " " << val << endl; exit(0); }
    for ( int i = pos; i <= l[x]; i += lowbit(i) ) 
        c[op][x][i] = min(c[op][x][i], val);
}

inline int Query(int op, int x, int pos)
{
    int ret = INF;
    for ( int i = pos; i > 0; i -= lowbit(i) ) ret = min(ret, c[op][x][i]);
    return ret;
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    size[u] = 1; int Max = 0; 
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; if ( v == fa || vis[v] ) continue ;
        DFS1(v, u); size[u] += size[v]; Max = max(Max, size[v]);
    }
    Max = max(Max, S - size[u]);
    if ( Max <= S / 2 ) Root = u;
}

inline void DFS2(int u, int fa)
{
    ++ S;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || vis[v] ) continue ;
        DFS2(v, u);
    }
}

inline void Solve(int u, int dep)
{
    l[u] = a[u].r - a[u].l + 1;
    c[0][u] = mem; mem += l[u] + 5; c[1][u] = mem; mem += l[u] + 5;
    REP(i, 1, l[u]) c[0][u][i] = c[1][u][i] = INF;
    queue<data> Q; 
    REP(i, a[u].l, a[u].r) 
    {
        int pos = Map[a[u].x][i]; dis[dep][pos] = pii(0, i - a[u].l + 1);
        belong[pos] = u; Q.push(data(a[u].x, i, 0, i - a[u].l + 1));
    }
    Dis[u] = dep; vis[u] = true;
    while ( !Q.empty() ) 
    {
        data x = Q.front(), y; Q.pop();
        REP(i, 0, 3)
        {
            y.x = x.x + dt[i][0]; y.y = x.y + dt[i][1];
            if ( !Map[y.x].count(y.y) ) continue ;
            int pos = Map[y.x][y.y];
            if ( vis[belong[pos]] || dis[dep][pos] != pii(-1, -1) ) continue ; 
            dis[dep][pos] = pii(x.dis + 1, x.pos);
            Q.push(data(y.x, y.y, x.dis + 1, x.pos));
        }
    }

    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( vis[v] ) continue ;
        S = 0; DFS2(v, u); DFS1(v, u); anc[Root] = u;
        Solve(Root, dep + 1);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n); m = 300000;
    REP(i, 1, n) { int x, y; scanf("%d%d", &x, &y); cell[x].push_back(y); Map[x][y] = i; }
    REP(i, 1, m)
    {
        sort(cell[i].begin(), cell[i].end());
        int lst = 0;
        for ( int j = 0; j + 1 < cell[i].size(); ++ j ) 
        {
            if ( cell[i][j] + 1 == cell[i][j + 1] ) continue ;
            a[++ tot] = node(i, cell[i][lst], cell[i][j]);
            Big[i].push_back(tot);
            lst = j + 1;
        }
        if ( lst != cell[i].size() ) 
        {
            a[++ tot] = node(i, cell[i][lst], cell[i].back());
            Big[i].push_back(tot);
        }
    }
    REP(i, 1, m - 1)
    {
        int pos = 0;
        for ( auto it : Big[i] ) 
        {
            while ( pos < Big[i + 1].size() && a[Big[i + 1][pos]].r < a[it].l ) ++ pos;
            while ( pos < Big[i + 1].size() && a[Big[i + 1][pos]].l <= a[it].r ) 
            {
                add(it, Big[i + 1][pos]); add(Big[i + 1][pos], it);
                ++ pos;
            }
            if ( pos ) -- pos;
        }
    }

    mem = C; memset(dis, -1, sizeof(dis)); 
    REP(i, 1, tot) if ( !vis[i] ) { S = 0; DFS2(i, 0); DFS1(i, 0); Solve(Root, 0); break ; }

    scanf("%d", &q); 
    while ( q -- ) 
    {
        int op, x, y; scanf("%d%d%d", &op, &x, &y); 
        int u = Map[x][y], pos = belong[u]; 
        if ( op == 1 )   
        {
            int dep = Dis[pos];
            while ( dep >= 0 )
            {
                Modify(0, pos, dis[dep][u].second, dis[dep][u].first - dis[dep][u].second);
                Modify(1, pos, l[pos] - dis[dep][u].second + 1, dis[dep][u].first + dis[dep][u].second);
                pos = anc[pos]; -- dep;
            }
        }
        else 
        {
            int ans = INF, dep = Dis[pos];
            while ( dep >= 0 )
            {
                ans = min(ans, dis[dep][u].first + dis[dep][u].second + Query(0, pos, dis[dep][u].second));
                ans = min(ans, dis[dep][u].first - dis[dep][u].second + Query(1, pos, l[pos] - dis[dep][u].second + 1));
                pos = anc[pos]; -- dep;
            }
            printf("%d\n", ans >= INF / 2 ? -1 : ans);
        }
    }
    return 0;
}
