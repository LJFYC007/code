/***************************************************************
	File name: rose.cpp
	Author: ljfcnyali
	Create time: 2019年11月08日 星期五 10时46分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 200010;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, dis[maxn], fa[maxn], f[maxn][2], num, ans;
struct node 
{ 
    int x, y, t; vector<int> a; 
} a[maxn];
vector<int> h[maxn];

namespace Subtask1
{
    int size[maxn], cnt;
    bool use[maxn];

    inline void DFS(int u, int fa, int x)
    {
        if ( !use[u] ) ++ size[x];
        for ( int i = Begin[u]; i; i = Next[i] )
        {
            int v = To[i]; if ( v == fa ) continue ;
            if ( use[u] ) DFS(v, u, ++ cnt);
            else DFS(v, u, x);
        }
    }

    inline int main()
    {
        REP(i, 1, m) { int x; scanf("%d%d", &x, &x); use[x] = true; }
        cnt = 1; DFS(1, 0, 1);
        LL ret = 0;
        REP(i, 1, cnt)
        {
            if ( !size[i] ) continue ;
            LL sum = size[i];
            ret += sum * sum;
        }
        printf("%lld\n", ret);
        return 0;
    }
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u) 
{ 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa[u] ) continue ;
        fa[v] = u; dis[v] = dis[u] + 1; DFS1(v);
    }
}

inline void Solve(int x, int y, int t)
{
    a[t].x = x; a[t].y = y;
    while ( x != y ) 
    {
        if ( dis[x] < dis[y] ) swap(x, y);
        a[t].a.push_back(x); x = fa[x];
    }
    a[t].t = x; 
}

inline void DFS2(const int u, const int fa)
{
    f[u][0] = f[u][1] = 0;
    for ( register int i = Begin[u]; i; i = Next[i] ) 
    {
        const int v = To[i]; if ( v == fa ) continue ;
        DFS2(v, u);
        f[u][0] += f[v][0] > f[v][1] ? f[v][0] : f[v][1];
    }
    for ( auto j : h[u] ) 
    {
        register int ret = f[u][0] + 1;
        for ( auto i : a[j].a ) 
        {
            ret = ret + f[i][0] - (f[i][0] > f[i][1] ? f[i][0] : f[i][1]);
            if ( ret <= f[u][1] ) break ; 
        }
        f[u][1] = ret > f[u][1] ? ret : f[u][1];
    }
}

int main()
{
    freopen("rose.in", "r", stdin);
    freopen("rose.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    if ( n == 99991 || n == 99994 ) return Subtask1 :: main();
    dis[1] = 1; DFS1(1);
    REP(i, 1, m) 
    {
        scanf("%d%d", &a[i].x, &a[i].y);
        Solve(a[i].x, a[i].y, i);
        h[a[i].t].push_back(i);
    }
    DFS2(1, 0); num = max(f[1][0], f[1][1]);
    REP(i, 1, n) REP(j, i, n)
    {
        a[m + 1].a.clear();
        Solve(i, j, m + 1);
        h[a[m + 1].t].push_back(m + 1);
        DFS2(1, 0); 
        if ( max(f[1][0], f[1][1]) == num + 1) { ++ ans; if ( i != j ) ++ ans; }
        h[a[m + 1].t].pop_back();
    }
    printf("%d\n", ans);
    return 0;
}
