/***************************************************************
	File name: POJ1039.cpp
	Author: ljfcnyali
	Create time: 2020年01月12日 星期日 09时56分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 110;

int n;
struct point { double x, y; } a[maxn];
struct Line { point a, b; } ;
double ans;

inline double multi(point p0, point p1, point p2)
{
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

inline bool Check(Line p1, Line p2)
{
    if ( max(p1.a.x, p1.b.x) < min(p2.a.x, p2.b.x) || max(p2.a.x, p2.b.x) < min(p1.a.x, p1.b.x) ) return false;
    if ( max(p1.a.y, p1.b.y) < min(p2.a.y, p2.b.y) || max(p2.a.y, p2.b.y) < min(p1.a.y, p1.b.y) ) return false;
    if ( multi(p1.a, p2.a, p1.b) * multi(p1.a, p1.b, p2.b) < 0 ) return false;
    if ( multi(p2.a, p1.a, p2.b) * multi(p2.a, p2.b, p1.b) < 0 ) return false;
    return true;
}

inline void Solve(int x, double x1, double y1, double x2, double y2)
{
    Line p1, p2;
    p1.a.x = x1; p1.a.y = y1; p1.b.x = x2; p1.b.y = y2;
    REP(i, 2, x)
    {
        p2.a.x = a[i - 1].x; p2.a.y = a[i - 1].y;
        p2.b.x = a[i].x; p2.b.y = a[i].y;
        if ( !Check(p1, p2) ) return ;
        -- p2.a.y; -- p2.b.y;
        if ( !Check(p1, p2) ) return ; 
    }
    double k1 = (p1.a.y - p1.b.y) / (p1.a.x - p1.b.x);
    double b1 = p1.a.y - k1 * p1.a.x;
    p1.b.x = 100000;
    p1.b.y = k1 * p1.b.x + b1;
    REP(i, x + 1, n)
    {
        p2.a.x = a[i - 1].x; p2.a.y = a[i - 1].y;
        p2.b.x = a[i].x; p2.b.y = a[i].y;
        if ( Check(p1, p2) )
        {
            double k1 = (p1.a.y - p1.b.y) / (p1.a.x - p1.b.x);
            double b1 = p1.a.y - k1 * p1.a.x;
            double k2 = (p2.a.y - p2.b.y) / (p2.a.x - p2.b.x);
            double b2 = p2.a.y - k2 * p2.a.x;
            double t = -(b1 - b2) / (k1 - k2);
            // printf("%.2lf\n", t);
            if ( t != (p2.a.y < p2.b.y ? a[i - 1].x : a[i].x) ) 
            {
                ans = max(ans, t);
                return ;
            }
        }
        -- p2.a.y; -- p2.b.y;
        if ( Check(p1, p2) )
        {
            double k1 = (p1.a.y - p1.b.y) / (p1.a.x - p1.b.x);
            double b1 = p1.a.y - k1 * p1.a.x;
            double k2 = (p2.a.y - p2.b.y) / (p2.a.x - p2.b.x);
            double b2 = p2.a.y - k2 * p2.a.x;
            double t = -(b1 - b2) / (k1 - k2);
            // printf("%.2lf\n", t);
            if ( t != (p2.a.y < p2.b.y ? a[i - 1].x : a[i].x) ) 
            {
                ans = max(ans, t);
                return ;
            }
            return ;
        }
    }
    // printf("%d %.2lf %.2lf %.2lf %.2lf\n", x, x1, y1, x2, y2);
    ans = 1000000000;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    // cin >> n;
    while ( ~scanf("%d", &n) )
    {
        if ( !n ) return 0;
        REP(i, 1, n) scanf("%lf%lf", &a[i].x, &a[i].y);
        ans = -1000000000;
        REP(i, 2, n)
        {
            Solve(i, a[1].x, a[1].y, a[i].x, a[i].y);
            Solve(i, a[1].x, a[1].y - 1, a[i].x, a[i].y);
            Solve(i, a[1].x, a[1].y, a[i].x, a[i].y - 1);
            Solve(i, a[1].x, a[1].y - 1, a[i].x, a[i].y - 1);
        }
        if ( ans == 1000000000 ) puts("Through all the pipe.");
        else printf("%.2lf\n", ans);
    }
    return 0;
}
