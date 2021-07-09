/***************************************************************
	File name: sphere.cpp
	Author: ljfcnyali
	Create time: 2020年09月10日 星期四 20时39分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define double long double
#define pii pair<double, double>
#define x first
#define y second
typedef long long LL;

const int maxn = 1e5 + 10;
const double pi = 3.14159265358979;

int n;
struct Node { int x, y, z, r; pair<int, int> p; } a[maxn], c[maxn];
struct node { pii x; double r; } b[maxn];

namespace Get
{
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

    inline double main(int n)
    {
        ans = 0; REP(i, 1, n) vis[i] = false;
        REP(i, 1, n) 
        { 
            a[i].x = b[i].x; a[i].r = b[i].r;
            a[i].x.y += 2000; 
            flag = false;
            REP(j, 1, i - 1) 
                if ( a[i].x.x > a[j].x.x - eps && a[i].x.x < a[j].x.x + eps 
                  && a[i].x.y > a[j].x.y - eps && a[i].x.y < a[j].x.y + eps 
                  && a[i].r > a[j].r - eps && a[i].r < a[j].r + eps ) flag = true;
            if ( flag ) { -- i; -- n; -- _end_; }
        }
        REP(i, 1, n) REP(j, 1, n) if ( i != j && Dis(a[i].x, a[j].x) + a[i].r < a[j].r + eps ) vis[i] = true;
        REP(i, 1, n)
        {
            if ( vis[i] ) continue ; p.clear();        
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
        return ans;
    }
}

const double eps = 1e-7;

inline double f(double x)
{
    int m = 0;
    REP(i, 1, n)
    {
        double t = c[i].r * c[i].r - (x - c[i].z) * (x - c[i].z);
        if ( t <= eps ) continue ;
        b[++ m].x = pii(c[i].x, c[i].y);
        b[m].r = sqrt(t);
    }
    return Get :: main(m);
}

inline double Simpson(double l, double r) { return (r - l) * (f(l) + f(r) + 4 * f((l + r) / 2)) / 6; }

inline double Solve(double l, double r)
{
    if ( l + eps > r ) return 0;
    double Mid = (l + r) / 2.0;
    double ret1 = Simpson(l, r), ret2 = Simpson(l, Mid) + Simpson(Mid, r);
    if ( ret1 > ret2 - eps && ret1 < ret2 + eps ) return ret1;
    return Solve(l, Mid) + Solve(Mid, r);
}

int main()
{ 
    freopen("sphere.in", "r", stdin);
    freopen("sphere.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) 
    {
        scanf("%d%d%d%d", &a[i].x, &a[i].y, &a[i].z, &a[i].r);
        a[i].p = pii(a[i].z - a[i].r, a[i].z + a[i].r);
    }
    sort(a + 1, a + n + 1, [](Node a, Node b) { return a.p < b.p; });
    double ans = 0;
    int lst = a[1].p.y, begin = a[1].p.x, pos = 1;
    REP(i, 1, n)
    {
        if ( a[i].p.x <= lst ) lst = max(a[i].p.y, lst);
        else 
        { 
            n = i - pos;
            REP(j, pos, i - 1) c[j - pos + 1] = a[j];
            ans += Solve(begin - 0.5, lst + 0.5); 
            pos = i; begin = a[i].p.x; lst = a[i].p.y; 
        }
    }
    n = n + 1 - pos;
    REP(j, pos, n) c[j - pos + 1] = a[j];
    ans += Solve(begin, lst);
    printf("%.3Lf\n", ans);
    return 0;
}
