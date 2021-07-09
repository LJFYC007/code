/***************************************************************
	File name: CF780H.cpp
	Author: ljfcnyali
	Create time: 2020年10月27日 星期二 16时28分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define pdd pair<double, double>
#define x first
#define y second
typedef long long LL;

const int maxn = 2e5 + 10;
const double eps = 1e-9;

int n, m, k;
double T, t[maxn], g[maxn];
pii a[maxn];
struct node 
{ 
    double l, r; int x, y; 
    node ( double a = 0, double b = 0, int c = 0, int d = 0 ) { l = a; r = b; x = c; y = d; }
} f[maxn];
struct data
{
    double k, b;
    data ( double x = 0, double y = 0 ) { k = x; b = y; } 
} A[maxn], B[maxn];
map<double, int> Map;

inline double sqr(double x) { return x * x; }
inline double Dis(pii a, pii b) { return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y)); }
inline double Get(double a, double b, double c, double x) { return a * x * x + b * x + c; }
inline data get(pdd a, pdd b) 
{
    double k = (a.y - b.y) / (a.x - b.x);
    return data(k, a.y - k * a.x);
}
inline data operator - (data a, data b) { return data(a.k - b.k, a.b - b.b); }

inline bool Check(double x)
{
    Map.clear(); vector<pdd> p; 
    REP(i, 1, k)
    {
        data l1 = data(A[f[i].x] - A[f[i].y]); l1.b -= T * A[f[i].y].k;
        data l2 = data(B[f[i].x] - B[f[i].y]); l2.b -= T * B[f[i].y].k;
        double a = l1.k * l1.k + l2.k * l2.k;
        double b = 2 * l1.k * l1.b + 2 * l2.k * l2.b;
        double c = l1.b * l1.b + l2.b * l2.b - x * x;
        double x1, x2;
        if ( !a && !b ) 
        {
            if ( c > 0 ) continue ;
            x1 = f[i].l; x2 = f[i].r;
        }
        else if ( !a ) x1 = x2 = -b / c;
        else 
        {   
            double delta = b * b - 4 * a * c;
            if ( delta < 0 ) continue ;
            delta = sqrt(delta);
            x1 = (delta - b) / a / 2; x2 = (-delta - b) / a / 2;
        }

        if ( x1 > x2 ) swap(x1, x2);
        x1 = max(f[i].l, x1); x2 = min(f[i].r, x2); 
        if ( x1 > x2 + eps ) continue ;
        if ( x2 - x1 >= T - eps ) 
        { 
            Map[0] += (int)((x2 - x1) / T);
            Map[T + eps] -= (int)((x2 - x1) / T);
            x1 = x1 + (int)((x2 - x1) / T) * T;
        }
        x1 = x1 - (int)(x1 / T) * T;
        x2 = x2 - (int)(x2 / T) * T;
        if ( x1 < x2 + eps ) p.push_back(pdd(x1, x2));
        else { p.push_back(pdd(x1, T)); p.push_back(pdd(0, x2)); }
    }

    for ( auto it : p ) { ++ Map[it.first]; -- Map[it.second + eps]; }
    int sum = 0;
    for ( auto it : Map ) { sum += it.second; if ( sum >= m ) return true; }
    return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) { scanf("%d%d", &a[i].x, &a[i].y); a[n + i] = a[i]; }
    REP(i, 1, n + n) 
    { 
        t[i] = Dis(a[i], a[i + 1]); 
        g[i] = g[i - 1] + t[i]; 
        A[i] = get(pdd(g[i - 1], a[i].x), pdd(g[i], a[i + 1].x));
        B[i] = get(pdd(g[i - 1], a[i].y), pdd(g[i], a[i + 1].y));
    }
    T = g[n] / m;
    int pos = 1; while ( g[pos] < T ) ++ pos;
    double lst = T - g[pos - 1];
    REP(i, 1, n)
    {
        double x = g[i - 1];
        while ( g[i] + T > g[pos] ) 
        { 
            f[++ k] = node(x, x + t[pos] - lst - 0.001, i, pos); 
            x += t[pos] - lst; lst = 0; ++ pos; 
        }
        f[++ k] = node(x, g[i] - 0.001, i, pos); lst = g[i] + T - g[pos - 1];
    }

    double l = 0, r = T;
    REP(o, 1, 65)
    {
        double Mid = (l + r) / 2.0;
        if ( Check(Mid) ) r = Mid;
        else l = Mid;
    }
    printf("%.10lf\n", (l + r) / 2.0);
    return 0;
}
