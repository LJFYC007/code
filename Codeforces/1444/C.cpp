/***************************************************************
  File name: C.cpp
Author: ljfcnyali
Create time: 2020年11月02日 星期一 21时17分25秒
 ***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, k, c[maxn], f[maxn], size[maxn], ans, tot;
struct node 
{ 
    int x, y, sz; 
    node ( int a = 0, int b = 0, int c = 0 ) { x = a; y = b; sz = c; }
} Stack[maxn * 5];
bool use[maxn];
map<pii, vector<pii> > Map;

inline int find(int x) { return x == f[x] ? x : find(f[x]); }

inline void Link(int x, int y)
{
    int fx = find(x), fy = find(y);
    if ( fx == fy ) return ;
    if ( size[fx] > size[fy] ) swap(fx, fy);
    Stack[++ tot] = node(fx, fy, size[fx]);
    size[fy] += size[fx]; f[fx] = fy;
}

inline void Pop()
{
    while ( tot ) 
    {
        size[Stack[tot].y] -= Stack[tot].sz;
        f[Stack[tot].x] = Stack[tot].x; -- tot;
    }
}

inline bool Merge(int x, int y)
{
    if ( find(x) == find(y) ) return 0;
    Link(x, n + y); Link(x + n, y); return 1;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &m, &k);
    REP(i, 1, n) scanf("%lld", &c[i]);
    REP(i, 1, n + n) { f[i] = i; size[i] = 1; }
    REP(i, 1, m)
    {
        int u, v; scanf("%lld%lld", &u, &v);
        if ( c[u] > c[v] ) swap(u, v);
        if ( c[u] == c[v] ) use[c[u]] |= !Merge(u, v);
        else Map[pii(c[u], c[v])].push_back(pii(u, v));
    }
    REP(i, 1, k) if ( !use[i] ) ++ ans; ans = ans * (ans - 1) / 2;
    tot = 0;
    for ( auto it : Map ) 
    {
        int i = it.first.first, j = it.first.second;
        if ( use[i] || use[j] ) continue ;
        for ( auto fuck : it.second ) 
            if ( !Merge(fuck.first, fuck.second) ) { -- ans; break ; }
        Pop();
    }
    printf("%lld\n", ans);
    return 0;
}
