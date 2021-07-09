/***************************************************************
	File name: c.cpp
	Author: ljfcnyali
	Create time: 2020年10月23日 星期五 18时46分08秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<double, double>
#define k first
#define b second
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 0x3f3f3f3f;
const double eps = 1e-12;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, dis[maxn];
int size[maxn], top[maxn], son[maxn], stop[maxn], f[maxn];
double ans = INF, T;
bool vis[maxn];
struct node 
{ 
    double t, c, u, v; 
    node ( double a = 0, double b = 0, double x = 0, double y = 0 ) { t = a; c = b; u = x; v = y; }
} ;
vector<node> a[maxn];
struct data
{
    double k, b, x1, x2;
    data ( double a = 0, double x = 0, double c = 0, double d = 0 ) { k = a; b = x; x1 = c; x2 = d; }
} line[maxn];
inline double get(data x) { return x.k * T + x.b; }
struct NODE
{
    int id; NODE ( int a = 0 ) { id = a; }
    inline bool operator < (const NODE a) const 
    { 
        double x = get(line[id]), y = get(line[a.id]);
        if ( abs(x - y) < eps ) return id < a.id;
        return x < y;
    } 
} ;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Update(int x, int y)
{
    if ( line[y].k == line[x].k )
    {
        if ( line[x].b == line[y].b ) ans = min(ans, max(line[x].x1, line[y].x1));
        return ;
    }
    double pos = (line[x].b - line[y].b) / (line[y].k - line[x].k);
    if ( pos < line[x].x1 - eps || pos < line[y].x1 - eps ) return ;
    if ( pos > line[x].x2 + eps || pos > line[y].x2 + eps ) return ;
    ans = min(ans, pos);
}

inline void Solve(vector<node> a)
{
    set<NODE> Set; vector<pii> f;   
    REP(i, 1, m) vis[i] = false; m = 0;
    for ( auto it : a ) 
    {
        if ( it.u > it.v ) it.c = -it.c; 
        line[++ m] = data(it.c, it.u - it.c * it.t, it.t, it.t + (it.v - it.u) * 1.0 / it.c);
        // cout << line[m].k << " " << line[m].b << " " << line[m].x1 << " " << line[m].x2 << endl;
        f.push_back(pii(m, line[m].x1)); f.push_back(pii(m, line[m].x2));
    }
    sort(f.begin(), f.end(), [](pii a, pii b) { return a.second < b.second; });
    if ( m <= 10000 ) REP(i, 1, m) REP(j, i + 1, m) Update(i, j);
    T = 0; 
    for ( auto it : f ) 
    {
        int x = it.first; bool gg = false;
        auto i = Set.find(x); T = it.second;
        if ( i == Set.end() )
        {
            if ( vis[x] ) 
            {
                auto i = ++ Set.begin();
                while ( i != Set.end() ) { auto itl = i; -- itl; Update(itl -> id, i -> id);  ++ i; }
                return ;
            }
            gg = vis[x] = true; Set.insert(NODE(x));
        }
        i = Set.find(x); if ( i == Set.end() ) return ;
        if ( i != Set.begin() ) { auto itl = i; -- itl; Update(itl -> id, i -> id); }
        if ( i != -- Set.end() ) { auto itr = i; ++ itr; Update(itr -> id, i -> id); }
        if ( gg == false ) { Set.erase(i); vis[x] = false; }
    }
}

inline void DFS1(int u, int fa)
{
    size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; f[v] = u;
        DFS1(v, u); size[u] += size[v];
        if ( size[v] > size[son[u]] ) son[u] = v;
    }
}

inline void DFS2(int u, int t)
{
    top[u] = t; stop[u] = u;
    if ( son[u] ) { DFS2(son[u], t); stop[u] = stop[son[u]]; }
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == f[u] || v == son[u] ) continue ;
        DFS2(v, v); 
    } 
}

inline int LCA(int x, int y)
{
    while ( top[x] != top[y] ) 
    {
        if ( dis[top[x]] < dis[top[y]] ) swap(x, y);
        x = f[top[x]];
    }
    return dis[x] < dis[y] ? x : y;
}

int main()
{
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS1(1, 0); DFS2(1, 1);
    REP(i, 1, m) 
    { 
        int c, u, v; double t; scanf("%lf%d%d%d", &t, &c, &u, &v); 
        int l = LCA(u, v); T = t + abs(dis[u] + dis[v] - 2 * dis[l]) * 1.0 / c;

        while ( top[u] != top[l] ) 
        {
            a[stop[u]].push_back(node(t, c, dis[u], dis[f[top[u]]]));
            t += abs(dis[f[top[u]]] - dis[u]) * 1.0 / c;
            u = f[top[u]];
        }
        if ( u != l ) a[stop[l]].push_back(node(t, c, dis[u], dis[l])); t += abs(dis[u] - dis[l]) * 1.0 / c;

        while ( top[v] != top[l] ) 
        {
            T -= abs(dis[f[top[v]]] - dis[v]) * 1.0 / c;
            a[stop[v]].push_back(node(T, c, dis[f[top[v]]], dis[v]));
            v = f[top[v]];
        }
        if ( v != l ) a[stop[l]].push_back(node(t, c, dis[l], dis[v]));
    }
    REP(i, 1, n) Solve(a[i]);
    printf("%.7lf\n", ans == INF ? -1 : ans);
    return 0;
}
