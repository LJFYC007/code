/***************************************************************
	File name: LibreOJ_3339.cpp
	Author: ljfcnyali
	Create time: 2020年08月30日 星期日 19时06分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const LL INF = 1e18;
const int maxn = 250 + 10;

int n, m, T, k, c[maxn];
LL A[maxn], B[maxn];
struct node { int t, x, y; } a[maxn];
struct Matrix { LL a[maxn][maxn]; } f, h[30];

inline Matrix operator * (Matrix a, Matrix b) 
{
    Matrix c;
    REP(i, 1, 5 * n) REP(j, 1, 5 * n) c.a[i][j] = -INF;
    REP(i, 1, 5 * n) REP(k, 1, 5 * n) if ( a.a[i][k] >= 0 ) REP(j, 1, 5 * n) c.a[i][j] = max(c.a[i][j], a.a[i][k] + b.a[k][j]);
    return c;
}

inline Matrix power(Matrix a, int b)
{
    Matrix r = a; -- b; if ( !b ) return r;
    while ( b ) { if ( b & 1 ) r = r * a; a = a * a; b >>= 1; } 
    return r;
}

inline void Mul(int t)
{
    REP(j, 0, 29) if ( (t >> j) & 1 )
    {
        REP(o, 1, n * 5) if ( A[o] >= 0 ) REP(s, 1, n * 5) B[s] = max(B[s], A[o] + h[j].a[o][s]); 
        REP(o, 1, n * 5) { A[o] = B[o]; B[o] = -INF; }
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d%d", &n, &m, &T, &k);
    REP(i, 1, n) scanf("%d", &c[i]);
    REP(i, 1, 5 * n) REP(j, 1, 5 * n) f.a[i][j] = -INF;
    REP(i, n + 1, 5 * n) f.a[i][i - n] = 0;
    REP(i, 1, m) 
    {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        f.a[(5 - w) * n + u][4 * n + v] = c[v];
    }
    h[0] = f;
    REP(i, 1, 29) h[i] = h[i - 1] * h[i - 1];
    REP(i, 1, k) scanf("%d%d%d", &a[i].t, &a[i].x, &a[i].y);    
    sort(a + 1, a + k + 1, [](node &a, node &b) { return a.t < b.t; });
    REP(o, 1, n * 5) A[o] = B[o] = -INF;
    A[4 * n + 1] = c[1];
    REP(i, 1, k) 
    {
        Mul(a[i].t - a[i - 1].t);
        A[4 * n + a[i].x] += a[i].y;
    }
    Mul(T - a[k].t);
    if ( A[4 * n + 1] >= 0 ) printf("%lld\n", A[4 * n + 1]);
    else puts("-1");
    return 0;
}
