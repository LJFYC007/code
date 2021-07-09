/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年06月18日 星期四 08时05分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;
const int INF = 1e18;

int n, m, last = 1, tot = 1, Root[4], f[maxn][4], Begin[maxn], Next[maxn], To[maxn], e, ans;
char s[maxn];
bool vis[maxn];
struct node { int Next[4], fa, len; } Tree[maxn];
struct Matrix { int a[4][4]; } g;
Matrix operator * (Matrix a, Matrix b)
{
    Matrix c;
    REP(i, 0, 3) REP(j, 0, 3)
    {
        c.a[i][j] = INF;
        REP(k, 0, 3) c.a[i][j] = min(c.a[i][j], a.a[i][k] + b.a[k][j]);
    }
    return c;
}
Matrix operator + (Matrix a, Matrix b)
{
    Matrix c;
    REP(i, 0, 3) REP(j, 0, 3) c.a[i][j] = min(INF, a.a[i][j] + b.a[i][j]);
    return c;
}

inline Matrix power(Matrix a, int b)
{
    Matrix r = a; -- b;
    while ( b ) { if ( b & 1 ) r = r * a; a = a * a; b >>= 1; } 
    return r;
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Extend(int c)
{
    int cur = ++ tot, p = last; last = cur; Tree[cur].len = Tree[p].len + 1;
    while ( p && !Tree[p].Next[c] ) { Tree[p].Next[c] = cur; p = Tree[p].fa; }
    if ( !p ) { Tree[cur].fa = 1; return ; }
    int q = Tree[p].Next[c];
    if ( Tree[p].len + 1 == Tree[q].len ) { Tree[cur].fa = q; return ; }
    int clone = ++ tot; Tree[clone] = Tree[q]; Tree[clone].len = Tree[p].len + 1;
    while ( p && Tree[p].Next[c] == q ) { Tree[p].Next[c] = clone; p = Tree[p].fa; }
    Tree[cur].fa = Tree[q].fa = clone;
}

inline void DFS(int u)
{
    if ( vis[u] ) return ;
    vis[u] = true;
    REP(j, 0, 3) f[u][j] = INF;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; DFS(v);
        REP(j, 0, 3) f[u][j] = min(f[u][j], f[v][j] + 1);
    }
    REP(j, 0, 3) if ( !Tree[u].Next[j] ) f[u][j] = min(f[u][j], 1ll);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%lld", &n);
    scanf("%s", s + 1); m = str(s + 1);
    REP(i, 1, m) Extend(s[i] - 'A');
    REP(i, 1, tot) REP(j, 0, 3) 
    {
        if ( Tree[i].Next[j] ) add(i, Tree[i].Next[j]); 
    }
    REP(j, 0, 3) f[0][j] = INF;
    DFS(1);
    REP(i, 0, 3) REP(j, 0, 3) g.a[i][j] = f[Tree[1].Next[i]][j];
    int L = 1, R = n;
    while ( L <= R ) 
    {
        int Mid = (L + R) >> 1;
        Matrix h = power(g, Mid);
        int Min = INF;
        REP(i, 0, 3) REP(j, 0, 3) Min = min(Min, h.a[i][j]);
        if ( Min < n ) { L = Mid + 1; ans = Mid; }
        else R = Mid - 1;
    }
    printf("%lld\n", ans + 1);
    return 0;
}
