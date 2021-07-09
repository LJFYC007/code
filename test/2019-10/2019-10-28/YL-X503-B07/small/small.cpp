/***************************************************************
	File name: small.cpp
	Author: ljfcnyali
	Create time: 2019年10月28日 星期一 08时35分52秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int Mod = 19491001;

int n;

struct Matrix
{
    int a[4][4], n, m;
    Matrix operator * (const Matrix &b) const
    {
        Matrix c; c.n = n; c.m = b.m;
        REP(i, 1, c.n) REP(j, 1, c.m) 
        {
            c.a[i][j] = 0;
            REP(k, 1, m) c.a[i][j] = (c.a[i][j] + a[i][k] * b.a[k][j]) % Mod;
        }
        return c;
    }
} f, g;

inline Matrix power(Matrix a, int b)
{
    Matrix r = a; -- b;
    while ( b ) { if ( b & 1 ) r = r * a; a = a * a; b >>= 1; }
    return r;
}

signed main()
{
    freopen("small.in", "r", stdin);
    freopen("small.out", "w", stdout);
    f.n = 3; f.m = 1; f.a[1][1] = 1; f.a[2][1] = 2; f.a[3][1] = 1;
    g.n = g.m = 3; g.a[1][2] = g.a[2][1] = g.a[2][2] = g.a[2][3] = g.a[3][3] = 1;
    scanf("%lld", &n);
    if ( n < 2 ) { puts("0"); return 0; }
    if ( n == 2 ) { puts("1"); return 0; }
    if ( n == 3 ) { puts("2"); return 0; }
    g = power(g, n - 3);
    f = g * f;
    printf("%lld\n", f.a[2][1]);
    return 0;
}
