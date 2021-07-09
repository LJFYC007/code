/***************************************************************
	File name: BZOJ2178.cpp
	Author: ljfcnyali
	Create time: 2020年09月08日 星期二 09时13分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<double, double>
#define x first
#define y second
typedef long long LL;

const int maxn = 1e5 + 10;
const double pi = 3.141592653589;
const double eps = 1e-12;

int n;
bool flag, vis[maxn];
double ans;
struct node { pii x; double r; } a[maxn];
vector<pii> p;

inline double Dis(pii a, pii b) { return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }

inline pii point(node a, double theta)
{
    return pii(a.x.x + a.r * cos(theta), a.x.y + a.r * sin(theta));
}

inline double calc(double r, double theta) { return r * r * (theta - sin(theta)) / 2.0; }

inline void Solve(node a, double l, double r)
{
    double size1 = calc(a.r, r - l);
    pii x1 = point(a, l), x2 = point(a, r);
    double size2 = (x1.y + x2.y) * (x1.x - x2.x) / 2.0;
    ans += size2 + size1;
}

int main()
{ 
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n)
    {
        scanf("%lf%lf%lf", &a[i].x.x, &a[i].x.y, &a[i].r);
        a[i].x.y += 2000;
        flag = false;
        REP(j, 1, i - 1) if ( a[i].x.x == a[j].x.x && a[i].x.y == a[j].x.y && a[i].r == a[j].r ) flag = true;
        if ( flag ) { -- i; -- n; -- _end_; }
    }
    REP(i, 1, n) REP(j, 1, n) if ( i != j && Dis(a[i].x, a[j].x) + a[i].r < a[j].r + eps ) vis[i] = true;
    REP(i, 1, n)
    {
        if ( vis[i] ) continue ;
        p.clear();        
        REP(j, 1, n)
        {
            if ( j == i || vis[j] ) continue ;
            double A = a[i].r, C = a[j].r, B = Dis(a[i].x, a[j].x);
            if ( A + B < C + eps || A + C < B + eps || B + C < A + eps ) continue ;
            double alpha = acos((A * A + B * B - C * C) / (2 * A * B));
            double theta = atan2(a[j].x.y - a[i].x.y, a[j].x.x - a[i].x.x);
            if ( theta < 0 ) theta += 2 * pi;
            double x = theta - alpha, y = theta + alpha;
            if ( y > 2 * pi ) y -= 2 * pi; if ( x < 0 ) x += 2 * pi;
            if ( y >= x ) p.push_back(pii(x, y)); 
            else { p.push_back(pii(x, 2 * pi)); p.push_back(pii(0, y)); } 
        }
        sort(p.begin(), p.end());
        double MaxRight = 0;
        for ( auto j : p ) 
        {
            if ( MaxRight < j.x + eps ) Solve(a[i], MaxRight, j.x);
            MaxRight = max(MaxRight, j.y);
        }
        if ( MaxRight < 2 * pi + eps ) Solve(a[i], MaxRight, 2 * pi);
    }
    printf("%.3lf\n", ans);
    return 0;
}
