/***************************************************************
	File name: P2742.cpp
	Author: ljfcnyali
	Create time: 2019年07月12日 星期五 15时02分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 10010;

struct Point
{
    double x, y;
    Point(double X = 0, double Y = 0) { x = X; y = Y; }
    bool operator < (const Point &a) const { return x < a.x || (x == a.x && y < a.y); }
    Point operator - (const Point &a) const { return Point(x - a.x, y - a.y); }
} a[maxn];

int n, Stack[maxn], top;
bool use[maxn];
double ans;

inline double cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }

inline double dis(Point a, Point b) 
{ 
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n); REP(i, 1, n) scanf("%lf%lf", &a[i].x, &a[i].y);
    sort(a + 1, a + n + 1);
    Stack[++ top] = 1;
    REP(i, 2, n)
    {
        while ( top >= 2 && cross(a[Stack[top]] - a[Stack[top - 1]], a[Stack[top]] - a[i]) <= 0 )
            use[Stack[top --]] = false;
        Stack[++ top] = i; use[i] = true;
    }
    REP(i, 2, top) ans += dis(a[Stack[i - 1]], a[Stack[i]]);
    top = 0;
    Stack[++ top] = n;
    for ( int i = n - 1; i >= 1; -- i )
    {
        if ( use[i] ) continue ;
        while ( top >= 2 && cross(a[Stack[top]] - a[Stack[top - 1]], a[Stack[top]] - a[i]) <= 0 )
            use[Stack[top --]] = false;
        Stack[++ top] = i; use[i] = true;
    }
    REP(i, 2, top) ans += dis(a[Stack[i - 1]], a[Stack[i]]);
    printf("%.2lf\n", ans);
    return 0;
}
