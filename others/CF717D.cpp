/***************************************************************
	File name: CF717D.cpp
	Author: ljfcnyali
	Create time: 2020年10月21日 星期三 11时06分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 128;

int n, m, k;
struct Matrix
{
    double a[maxn][maxn];
} A;

inline Matrix operator * (Matrix a, Matrix b)
{
    Matrix c; REP(i, 0, n) REP(j, 0, n) c.a[i][j] = 0;
    REP(i, 0, n) REP(j, 0, n) REP(k, 0, n) c.a[i][j] += a.a[i][k] * b.a[k][j];
    return c;
}

inline Matrix power(Matrix a, int b)
{
    Matrix r = a; -- b;
    while ( b ) { if ( b & 1 ) r = r * a; a = a * a; b >>= 1; } 
    return r;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &k, &m); n = 127;
    REP(i, 0, m) 
    {
        double x; scanf("%lf", &x);
        REP(j, 0, n) A.a[j][j ^ i] += x;
    }
    A = power(A, k);
    printf("%.6lf\n", 1 - A.a[0][0]);
    return 0;
}
