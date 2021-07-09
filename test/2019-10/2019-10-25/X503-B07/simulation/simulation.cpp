/***************************************************************
	File name: simulation.cpp
	Author: ljfcnyali
	Create time: 2019年10月25日 星期五 09时32分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1610;

int n, m, T, num, s, t;
bool use[60][20];
struct node { int u, v, w; } a[maxn];
struct Matrix
{
    int n, m, a[60][60];
    Matrix operator * (const Matrix b) const
    {
        Matrix c; c.n = n; c.m = b.m;
        REP(i, 1, c.n) REP(j, 1, c.m)
        {
            c.a[i][j] = 0;
            REP(k, 1, m) c.a[i][j] = max(c.a[i][j], a[i][k] * b.a[k][j]);
        }
        return c;
    }
} f[20], g, p, A;

inline Matrix power(Matrix a, int b)
{
    Matrix r = a; -- b;
    while ( b ) { if ( b & 1 ) r = r * a; a = a * a; b >>= 1; }
    return r;
}

inline bool Check(int x)
{
    REP(i, 1, 12) REP(j, 1, n) REP(k, 1, n) f[i].a[j][k] = false;
    REP(i, 1, n) g.a[i][1] = 0;
    REP(i, 1, m)
    {
        if ( a[i].u == s && use[a[i].v][1] && a[i].w <= x ) g.a[a[i].v][1] = 1;
        if ( a[i].v == s && use[a[i].u][1] && a[i].w <= x ) g.a[a[i].u][1] = 1;
    }
    REP(i, 1, 12)
        REP(j, 1, m)
        {
            if ( a[j].w > x ) continue ;
            int now = i, nex = i % 12 + 1;
            int u = a[j].u, v = a[j].v;
            if ( use[u][now] && use[v][nex] ) f[i].a[v][u] = true;
            if ( use[v][now] && use[u][nex] ) f[i].a[u][v] = true;
        }
    p = f[T % 12]; 
    for ( int i = (T % 12) - 1; i >= 1; -- i ) p = p * f[i];
    if ( T >= 12 ) 
    {
        A = f[12];
        for ( int i = 11; i >= 1; -- i ) A = A * f[i];
        p = p * power(A, T / 12);
    }
    p = p * g;
    return p.a[t][1];
}

int main()
{
    freopen("simulation.in", "r", stdin);
    freopen("simulation.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &T);
    REP(i, 1, m) scanf("%d%d%d", &a[i].u, &a[i].v, &a[i].w);
    memset(use, true, sizeof(use));
    scanf("%d%d%d", &num, &s, &t);
    if ( s == t && !T ) { puts("0"); return 0; }
    REP(i, 1, num)
    {
        int x; scanf("%d", &x);
        REP(j, 1, x)
        {
            int y; scanf("%d", &y);
            for ( int k = j; k <= 12; k += x ) use[y][k] = false;
        }
    }
    REP(i, 1, 12) f[i].n = f[i].m = n;
    g.n = n; g.m = 1;
    -- T;
    int L = 0, R = 1000000, ans = -1;
    while ( L <= R ) 
    {
        int Mid = L + R >> 1;
        if ( Check(Mid) ) { ans = Mid; R = Mid - 1; }
        else L = Mid + 1;
    }
    if ( ans == -1 ) puts("impossible");
    else printf("%d\n", ans);
    return 0;
}
