/***************************************************************
	File name: P3803.cpp
	Author: ljfcnyali
	Create time: 2019年06月28日 星期五 11时17分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 4000010;
const double Pi = acos(-1);

int n, m, r[maxn];

struct Complex
{
    double x, y;
    Complex(double X = 0, double Y = 0) { x = X, y = Y; }
} a[maxn], b[maxn];
Complex operator + (Complex a, Complex b) 
{
    return Complex(a.x + b.x, a.y + b.y);
}
Complex operator - (Complex a, Complex b)
{
    return Complex(a.x - b.x, a.y - b.y);
}
Complex operator * (Complex a, Complex b)
{
    return Complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

inline void FFT(Complex *f, int opt)
{
    REP(i, 0, n - 1) if ( i < r[i] ) swap(f[i], f[r[i]]);
    for ( int p = 2; p <= n; p <<= 1 )
    {
        int len = p / 2;
        Complex tmp(cos(Pi / len), opt * sin(Pi / len));
        for ( int k = 0; k < n; k += p )
        {
            Complex buf(1, 0);
            REP(i, k, k + len - 1)
            {
                Complex tt = buf * f[len + i];
                f[len + i] = f[i] - tt;
                f[i] = f[i] + tt;
                buf = buf * tmp;
            }
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 0, n) scanf("%lf", &a[i].x);
    REP(i, 0, m) scanf("%lf", &a[i].y);
    m += n; n = 1;
    while ( n <= m ) n <<= 1;
    REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
    FFT(a, 1); //FFT(b, 1);
    REP(i, 0, n - 1) a[i] = a[i] * a[i];
    FFT(a, -1);
    REP(i, 0, m) printf("%.0lf ", fabs(a[i].y) / n / 2);
    return 0;
}
