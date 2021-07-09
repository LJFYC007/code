/***************************************************************
	File name: a.cpp
	Author: ljfcnyali
	Create time: 2019年11月06日 星期三 19时27分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;
const double eps = 1e-10;

int n, m, a[maxn], b[maxn];

inline bool Check(double x)
{
    REP(i, 1, n)
    {
        double t = (x + m) / a[i];
        x -= t; if ( x < 0 ) return false; 
        t = (x + m) / b[i];
        x -= t; if ( x < 0 ) return false;
    } 
    return true;
}

int main()
{
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n) scanf("%d", &b[i]);
    double L = 0, R = 1000000000, ans = -1;
    REP(i, 1, 10000)
    {
        double Mid = (L + R) / 2;
        if ( Check(Mid) ) { ans = Mid; R = Mid - eps; }
        else L = Mid + eps;
    }
    if ( ans < 0 ) puts("-1");
    else printf("%.9lf\n", ans);
    return 0;
}
