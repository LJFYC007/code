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
#define int long long
#define pii pair<int, int>
#define x first
#define y second
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 5e5 + 10;
const double INF = 1e18;
const int N = 1e9;

int n, c[maxn], Begin[maxn], Next[maxn], To[maxn], e, dis[maxn], tot;
int Root[maxn];
double ans[maxn];
struct node { int lson, rson; bool flag; pii x; } Tree[maxn * 10];

inline double f(pii a, double pos) { return a.x + pos * a.y; }

inline double find(pii a, pii b) { return (b.x - a.x) * 1.0 / (a.y - b.y); }

inline int Modify(int now, double l, double r, pii x, int dep)
{
    if ( dep == 51 ) return 0;
    int root = ++ tot; Tree[root] = Tree[now];
    if ( !Tree[root].flag ) { Tree[root].flag = true; Tree[root].x = x; return root; } 
    double Mid = (l + r) / 2.0;
    if ( f(x, Mid) < f(Tree[root].x, Mid) ) swap(Tree[root].x, x);
    if ( x.y > Tree[root].x.y ) ls(root) = Modify(ls(root), l, Mid, x, dep + 1);
    else rs(root) = Modify(rs(root), Mid, r, x, dep + 1);
    return root;
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
    if ( u != 1 ) ans[u] = Query(Root[u], -N, N, pii(c[u], dis[u]), 0);
    Root[u] = Modify(Root[u], -N, N, pii(c[u], dis[u]), 0);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; dis[v] = dis[u] + 1;
        Root[v] = Root[u]; DFS(v);
    }
}

signed main()
{
    freopen("lost.in", "r", stdin);
    freopen("lost.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld", &c[i]);
    REP(i, 2, n) { int x; scanf("%lld", &x); add(x, i); }
    dis[1] = 1; DFS(1);  
    REP(i, 2, n) printf("%.7lf\n", ans[i]);
    return 0;
}
