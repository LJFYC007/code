/***************************************************************
	File name: P5303.cpp
	Author: ljfcnyali
	Create time: 2019年10月28日 星期一 16时15分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int Mod = 1e9 + 7;

int n;

struct Matrix
{
    int n, m, a[6][6];
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
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T; scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld", &n); 
        if ( n < 3 ) { puts("0"); continue ; }  
        REP(i, 1, 5) REP(j, 1, 5) f.a[i][j] = g.a[i][j] = 0;
        f.n = 5; f.m = f.a[3][1] = 1; f.a[4][1] = f.a[5][1] = 2;
        g.n = g.m = 5; g.a[1][2] = g.a[2][1] = g.a[2][2] = g.a[3][4] = g.a[4][3] = g.a[4][4] = g.a[5][5] = 1; g.a[2][4] = 2; g.a[2][5] = -1;
        g = power(g, n - 2);
        f = g * f;
        printf("%lld\n", (f.a[2][1] + Mod) % Mod);
    }
    return 0;
}
