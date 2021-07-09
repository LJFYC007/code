/***************************************************************
	File name: P4525.cpp
	Author: ljfcnyali
	Create time: 2020年09月07日 星期一 20时50分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const double eps = 1e-9;

double a, b, c, d, L, R;

inline double f(double x) { return (c * x + d) / (a * x + b); }

inline double calc(double l, double r) { return (r - l) * (f(l) + f(r) + 4 * f((l + r) / 2.0)) / 6.0; }

inline double Solve(double l, double r)
{
    if ( l + eps > r ) return 0;
    double Mid = (l + r) / 2.0;
    double ret1 = calc(l, r), ret2 = calc(l, Mid) + calc(Mid, r);
    if ( ret2 - eps <= ret1 && ret1 <= ret2 + eps ) return ret1; 
    return Solve(l, Mid) + Solve(Mid, r);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin >> a >> b >> c >> d >> L >> R;
    printf("%.6lf\n", Solve(L, R));
    return 0;
}
