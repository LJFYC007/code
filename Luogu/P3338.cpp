/***************************************************************
	File name: P3338.cpp
	Author: ljfcnyali
	Create time: 2019年06月28日 星期五 14时30分52秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 2400010;
const double Pi = acos(-1);

struct Complex
{
    double x, y;
    Complex(double X = 0, double Y = 0) { x = X; y = Y; }
} a[maxn], b[maxn], c[maxn];
int r[maxn], n, m;

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
                Complex tt = f[len + i] * buf;
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
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%lf", &a[i].x); b[n - i + 1].x = a[i].x; c[i].x = (double)(1.0 / i) / i; }
    m = n; n = 1;
    while ( n <= (m << 1) ) n <<= 1;
    REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
    FFT(a, 1); FFT(b, 1); FFT(c, 1);
    REP(i, 0, n - 1) { a[i] = a[i] * c[i]; b[i] = b[i] * c[i]; }
    FFT(a, -1); FFT(b, -1);
    REP(i, 0, n - 1) { a[i].x /= n; b[i].x /= n; }
//    REP(i, 1, m) printf("%.4lf ", a[i].x); puts("");
//    REP(i, 1, m) printf("%.4lf ", b[i].x); puts("");
    REP(i, 1, m) 
    {
        double x = b[m - i + 1].x;
        double y = a[i].x;
//        printf("%.4lf %.4lf\n", y, x);
        printf("%.4lf\n", y - x);
    }
    return 0;
}
