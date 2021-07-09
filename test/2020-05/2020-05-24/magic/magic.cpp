/***************************************************************
	File name: magic.cpp
	Author: ljfcnyali
	Create time: 2020年05月24日 星期日 08时50分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int unsigned int 
typedef long long LL;

const int maxn = 110;

int n, m, q;
struct Matrix { int n, m, a[maxn][maxn]; } f, g, h, QaQ[maxn];
Matrix operator * (Matrix a, Matrix b)
{
    Matrix c; c.n = a.n; c.m = b.m;
    REP(i, 1, c.n) REP(j, 1, c.m)
    {
        c.a[i][j] = 0;
        REP(k, 1, a.m) c.a[i][j] ^= a.a[i][k] * b.a[k][j];
    }
    return c;
}

inline Matrix power(int n)
{
    Matrix a = g; n --;
    while ( n ) 
    {
        if ( n & 1 ) a = a * g;
        g = g * g; n >>= 1;
    }
    return a;
}

signed main()
{
    freopen("magic.in", "r", stdin);
    freopen("magic.out", "w", stdout);
    scanf("%u%u%u", &n, &m, &q);
    f.n = 1; f.m = n;
    REP(i, 1, n) scanf("%u", &f.a[1][i]);
    g.n = g.m = n;
    REP(i, 1, m) { int u, v; scanf("%u%u", &u, &v); g.a[u][v] = g.a[v][u] = 1; }
    QaQ[0] = g;
    REP(i, 1, 31) QaQ[i] = QaQ[i - 1] * QaQ[i - 1];
    while ( q -- ) 
    {
        int x; scanf("%u", &x);
        h = f;
        for ( int i = 31; i >= 0; -- i ) 
        {
            if ( (x >> i) & 1 ) h = h * QaQ[i];
            if ( i == 0 ) break ; 
        }
        printf("%u\n", h.a[1][1]);
    }
    return 0;
}
