/***************************************************************
	File name: lost.cpp
	Author: ljfcnyali
	Create time: 2020年10月03日 星期六 09时21分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 5e5 + 10;
const double INF = 1e18;
const int N = 5e8;

int n, c[maxn], Begin[maxn], Next[maxn], To[maxn], e, dis[maxn], tot, Root, X;
int Rub[maxn], top, cnt;
double ans[maxn];
struct node { int lson, rson; bool flag; pii x; } Tree[maxn * 5];
vector< pair<in, node> > p[101];
vector<int> g[101];

inline int NewNode()
{
    int x; 
    if ( top > 0 ) 
    {
        x = Rub[top --]; 
        ls(x) = rs(x) = Tree[x].flag = 0;
    }
    else x = ++ tot;
    return x;
}

inline double f(pii a, double pos) { return a.x + pos * a.y; }

inline double find(pii a, pii b) { return (b.x - a.x) * 1.0 / (a.y - b.y); }

inline void Modify(int &root, double l, double r, pii x, int dep)
{
    if ( dep == 51 ) return ;
    if ( !root ) { root = NewNode(); if ( X ) g[X].push_back(root); }
    if ( X ) p[X].push_back(make_pair(root, Tree[root]));
    if ( !Tree[root].flag ) { Tree[root].flag = true; Tree[root].x = x; } 
    double Mid = (l + r) / 2.0;
    if ( f(x, Mid) < f(Tree[root].x, Mid) ) swap(Tree[root].x, x);
    if ( x.y > Tree[root].x.y ) Modify(ls(root), l, Mid, x, dep + 1);
    else Modify(rs(root), Mid, r, x, dep + 1);
}

inline double Query(int root, double l, double r, pii x, int dep)
{
    if ( !root || dep == 51 ) return INF; 
    double pos = find(x, Tree[root].x), Mid = (l + r) / 2.0;
    if ( pos < Mid ) pos = min(pos, Query(ls(root), l, Mid, x, dep + 1)); 
    else pos = min(pos, Query(rs(root), Mid, r, x, dep + 1));
    return pos;
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u)
{
    if ( u != 1 ) ans[u] = Query(Root, -N, N, pii(c[u], dis[u]), 0);
    if ( u <= 100 ) X = u; else X = 0; 
    Modify(Root, -N, N, pii(c[u], dis[u]), 0);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; dis[v] = dis[u] + 1;
        DFS(v);
    }
    if ( u <= 100 ) 
    {
        for ( auto it : p[u] ) Tree[it.first] = it.second;
        for ( auto it : g[u] ) Rub[++ top] = it;
    }
}

signed main()
{
    freopen("lost.in", "r", stdin);
    freopen("lost.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &c[i]);
    REP(i, 2, n) { int x; scanf("%d", &x); add(x, i); }
    dis[1] = 1; DFS(1);  
    REP(i, 2, n) printf("%.7lf\n", ans[i]);
    return 0;
}
