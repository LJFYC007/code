/***************************************************************
	File name: P3829.cpp
	Author: ljfcnyali
	Create time: 2019年07月12日 星期五 15时45分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const double Pi = acos(-1);
const int maxn = 100010;

struct Point
{
    double x, y;
    Point(double X = 0, double Y = 0) { x = X; y = Y; }
    bool operator < (const Point &a) const { return x < a.x || (x == a.x && y < a.y); }
    Point operator - (const Point &a) const { return Point(x - a.x, y - a.y); }
} a[maxn];

inline double cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }

inline double Dis(Point a, Point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int n, Stack[maxn], top, cnt;
double A, B, R, ans, L, angle[4];
bool use[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    cin >> A >> B >> R;
    ans = 2 * Pi * R; A -= 2 * R; B -= 2 * R;
    L = sqrt(A * A + B * B) / 2;
    angle[0] = atan(A / B); angle[1] = Pi - angle[0];
    angle[2] = Pi + angle[0]; angle[3] = 2 * Pi - angle[0];
    REP(i, 1, n)
    {
        double x, y, k; scanf("%lf%lf%lf", &x, &y, &k);
        REP(j, 0, 3)
        {
            a[++ cnt].x = cos(k + angle[j]) * L + x;
            a[cnt].y = sin(k + angle[j]) * L + y;
//            printf("%.2lf %.2lf\n", a[cnt].x, a[cnt].y);
        }
    }
    n = cnt;
    sort(a + 1, a + n + 1);
    Stack[++ top] = 1;
    REP(i, 2, n)
    {
        while ( top >= 2 && cross(a[Stack[top]] - a[Stack[top - 1]], a[Stack[top]] - a[i]) <= 0 ) 
            use[Stack[top --]] = false;
        Stack[++ top] = i; use[i] = true;
    }
    REP(i, 2, top) ans += Dis(a[Stack[i]], a[Stack[i - 1]]);
    top = 0;
    Stack[++ top] = n;
    for ( int i = n - 1; i >= 1; -- i )
    {
        if ( use[i] ) continue ;
        while ( top >= 2 && cross(a[Stack[top]] - a[Stack[top - 1]], a[Stack[top]] - a[i]) <= 0 ) 
            use[Stack[top --]] = false;
        Stack[++ top] = i; use[i] = true;
    }
    REP(i, 2, top) ans += Dis(a[Stack[i]], a[Stack[i - 1]]);
    printf("%.2lf\n", ans);
    return 0;
}
