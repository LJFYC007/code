/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年06月18日 星期四 10时20分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;
const int Mod = 1e9 + 7;

int n, m, op, Begin[maxn], Next[maxn], To[maxn], e, p[maxn], size[maxn];
int dis[maxn], dfn[maxn], low[maxn], tot, top, Stack[maxn], cnt, Root[maxn];
map<int, int> Map;
struct Matrix { bitset<210> a[210]; } a, b, c, d, E;
Matrix operator * (Matrix a, Matrix b)
{
    Matrix c;
    REP(i, 1, n) c.a[i].reset();
    REP(i, 1, n) REP(j, 1, n) if ( a.a[i][j] ) c.a[i] |= b.a[j];
    return c;
}
Matrix operator + (Matrix a, Matrix b)
{
    Matrix c;
    REP(i, 1, n) c.a[i] = a.a[i] | b.a[i];
    return c;
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline Matrix power(Matrix a, int b)
{
    Matrix r = a; -- b;
    while ( b ) { if ( b & 1 ) r = r * a; a = a * a; b >>= 1; } 
    return r;
}

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void Tarjan(int u)
{
    dfn[u] = low[u] = ++ tot; Stack[++ top] = u;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i];
        if ( !dfn[v] ) { Tarjan(v); low[u] = min(low[u], low[v]); }
        else if ( !p[v] ) low[u] = min(low[u], dfn[v]);
    }
    if ( low[u] == dfn[u] ) 
    {
        p[u] = ++ cnt; ++ size[cnt]; Root[cnt] = u;
        while ( Stack[top] != u ) { p[Stack[top]] = cnt; -- top; ++ size[cnt]; }
        -- top;
    }
}

inline void DFS(int u, int x)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( p[v] != x ) continue ;
        if ( !dis[v] ) { dis[v] = dis[u] + 1; DFS(v, x); }
        else size[x] = __gcd(size[x], abs(dis[u] - dis[v] + 1));
    }
}

inline bool check()
{
    REP(i, 1, n) REP(j, 1, n) if ( d.a[i][j] != E.a[i][j] ) return false;
    return true;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &m, &op);
    REP(i, 1, m) 
    { 
        int x, y; scanf("%lld%lld", &x, &y); 
        add(x, y); 
        if ( op == 1 ) a.a[x].set(y);
    }
    REP(i, 1, n) if ( !dfn[i] ) Tarjan(i);
    REP(i, 1, cnt) { dis[Root[i]] = 1; DFS(Root[i], i); }
    int ans = 1;
    REP(i, 1, cnt)
    {
        int x = size[i];
        for ( int j = 2; j * j <= x; ++ j ) 
        {
            if ( x % j != 0 ) continue ;
            int num = 0;
            while ( x % j == 0 ) { ++ num; x /= j; }
            Map[j] = max(Map[j], num);
        }
        Map[x] = max(Map[x], 1ll);
    }
    if ( op == 1 ) b = c = a;
    for ( auto i : Map ) 
    {
        ans = ans * power(i.first, i.second) % Mod;
        if ( op == 1 ) b = power(b, power(i.first, i.second));
    }
    if ( op == 1 ) b = b * a;
    if ( op == 1 ) 
    {
        int ret = 1, L = 0, R = 40000;
        d = b; E = c;
        if ( check() ) { printf("1 "); goto Next ; }
        while ( L <= R ) 
        {
            int Mid = (L + R) >> 1;
            d = b * power(a, Mid - 1); 
            E = c * power(a, Mid - 1);
            if ( check() ) { ret = Mid; R = Mid - 1; }
            else L = Mid + 1;
        }
        printf("%lld ", ret);
    }
Next : ;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
