/***************************************************************
	File name: P2831.cpp
	Author: ljfcnyali
	Create time: 2019年06月27日 星期四 09时40分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1 << 18;
const double eps = 0.000000001;

int f[maxn], n, m;
double x[maxn], y[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T; scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d", &n, &m);
        REP(i, 1, n) scanf("%lf%lf", &x[i], &y[i]);
        memset(f, 0x3f, sizeof(f));
        f[0] = 0;
        int p = 1;
        REP(i, 1, n)
        {
            f[p] = 1; p *= 2;
        }
        int num = 1 << n;
        REP(s, 0, num - 1)
        {
            REP(i, 1, n - 1)
            {
                if ( (s >> (i - 1)) & 1 ) continue ;
                f[s | (1 << (i - 1))] = min(f[s | (1 << (i - 1))], f[s] + 1);
                REP(j, i + 1, n)
                {
                    if ( (s >> (j - 1)) & 1 ) continue ;
                    f[s | (1 << (j - 1))] = min(f[s | (1 << (j - 1))], f[s] + 1);
                    int cnt = s | (1 << (i - 1));
                    cnt = cnt | (1 << (j - 1));
                    if ( fabs(x[i] - x[j]) < eps ) continue ;
//                    a * x[i] * x[i] * (x[j] - x[i]) = y[i] * x[j] - y[j] * x[i]
//                    a * x[j] * x[j] + b * x[j] = y[j]
                    double a = y[i] * x[j] - y[j] * x[i];
                    a /= x[i] * x[j] * (x[i] - x[j]) * 1.0;
                    double b = y[i] - a * x[i] * x[i];
                    b = b * 1.0 / x[i];
                    if ( a > -eps ) continue ;
//                    printf("%lf %lf\n", a, b);
                    REP(k, 1, n) 
                    {
                        if ( k == i || k == j ) continue ;
                        if ( fabs(a * x[k] * x[k] + b * x[k] - y[k]) < eps ) cnt = cnt | (1 << (k - 1));
                    }
                    f[cnt] = min(f[cnt], f[s] + 1);
                }
            }
        }
//        REP(i, 0, num - 1) printf("%d ", f[i]);
        printf("%d\n", f[num - 1]);
    }
    return 0;
}
