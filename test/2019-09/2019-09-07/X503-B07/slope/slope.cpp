/***************************************************************
	File name: slope.cpp
	Author: ljfcnyali
	Create time: 2019年09月07日 星期六 08时45分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 200010;

struct node
{
    double x, y, p;
    bool operator < (const node &a) const { return p < a.p; }
} a[maxn];
int n, ansx = 1, ansy = 1;
double P, Q;

int main()
{
    freopen("slope.in", "r", stdin);
    freopen("slope.out", "w", stdout);
    scanf("%d%lf%lf", &n, &P, &Q);
    REP(i, 1, n) { scanf("%lf%lf", &a[i].x, &a[i].y); a[i].p = a[i].y - P * a[i].x / Q; }
    sort(a + 1, a + n + 1);
    REP(i, 1, n)
    {
        if ( i > 1 ) 
        {
            if ( a[i - 1].x < a[i].x && a[i - 1].y > a[i].y ) goto next ;
            if ( a[i - 1].x > a[i].x && a[i - 1].y < a[i].y ) goto next ;
            int sumx = a[i].x - a[i - 1].x, sumy = a[i].y - a[i - 1].y;
            if ( abs(sumy * 1.0 / sumx - P / Q) < abs(ansy * 1.0 / ansx - P / Q) ) ansx = sumx, ansy = sumy;
            if ( abs(sumy * 1.0 / sumx - P / Q) == abs(ansy * 1.0 / ansx - P / Q) && sumx * ansy > sumy * ansx ) ansx = sumx, ansy = sumy;
        }
next: ; 
        if ( i < n )
        {
            if ( a[i + 1].x < a[i].x && a[i + 1].y > a[i].y ) continue ;
            if ( a[i + 1].x > a[i].x && a[i + 1].y < a[i].y ) continue ;
            int sumx = a[i].x - a[i + 1].x, sumy = a[i].y - a[i + 1].y;
            if ( abs(sumy * 1.0 / sumx - P / Q) < abs(ansy * 1.0 / ansx - P / Q) ) ansx = sumx, ansy = sumy;
            if ( abs(sumy * 1.0 / sumx - P / Q) == abs(ansy * 1.0 / ansx - P / Q) && sumx * ansy > sumy * ansx ) ansx = sumx, ansy = sumy;
        }
    }
    int t = __gcd(ansx, ansy);
    printf("%d/%d\n", ansy / t, ansx / t);
    return 0;
}
