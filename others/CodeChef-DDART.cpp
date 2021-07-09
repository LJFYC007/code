/***************************************************************
	File name: CodeChef-DDART.cpp
	Author: ljfcnyali
	Create time: 2020年12月24日 星期四 16时02分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<double, double>
#define x first
#define y second
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
#define double long double
typedef long long LL;

const int maxn = 1e6 + 10;
const double eps = 1e-9;
const double INF = 1e18;
const double pi = 3.1415926535;

int q, n = 3, tot, Root;
struct node { pii point; int r; } a[maxn];
struct Node { pii line; bool flag; int lson, rson; } Tree[maxn * 5];
pii Delta;
double theta;

inline pii operator + (pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
inline pii operator * (pii a, double b) { return pii(a.x * b, a.y * b); }
inline double sqr(double x) { return x * x; }
inline double Dis(pii a, pii b = pii(0, 0)) { return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y)); }
inline double calc(pii a, pii b = pii(0, 0)) { return (b.y - a.y) / (b.x - a.x); }
inline void Change(pii &x) { x = pii(x.x * cos(theta) - x.y * sin(theta), x.x * sin(theta) + x.y * cos(theta)); }
inline double f(pii x, double pos) { return x.x + pos * x.y; }

inline void Modify(int &root, double l, double r, pii x)
{
    if ( !root ) root = ++ tot;
    if ( !Tree[root].flag ) { Tree[root].flag = true; Tree[root].line = x; return ; } 
    double Mid = (l + r) / 2;
    if ( f(Tree[root].line, Mid) > f(x, Mid) ) swap(Tree[root].line, x);
    if ( x.y > Tree[root].line.y ) Modify(ls(root), l, Mid, x);
    else Modify(rs(root), Mid, r, x);
}

inline double Query(int root, double l, double r, double x)
{
    if ( !root ) return INF;
    double Mid = (l + r) / 2, ret = f(Tree[root].line, x);
    if ( x <= Mid )
        ret = min(ret, Query(ls(root), l, Mid, x));
    else 
        ret = min(ret, Query(rs(root), Mid, r, x));
    // cout << root << " " << ret << endl;
    return ret;
}

inline bool Check(double x, double y, int i) 
{
    double len = sqr(Dis(pii(x, y), a[i].point)) - a[i].r;
    return -eps < len && len < eps; 
}

inline void Solve(node a, node b)
{
    double L = Dis(a.point, b.point), K1 = calc(a.point, b.point), K2 = -1 / K1; 
    double AE = (a.r - b.r + L * L) / (2 * L);
    double x0 = a.point.x + (AE / L) * (b.point.x - a.point.x);
    double y0 = a.point.y + (AE / L) * (b.point.y - a.point.y);
    double CE = sqrt(a.r - sqr(Dis(pii(x0, y0), a.point)));
    double x1 = x0 - CE / sqrt(1 + K2 * K2);
    double y1 = y0 + K2 * (x1 - x0);
    if ( !Check(x1, y1, 3) ) { x1 = x0 + CE / sqrt(1 + K2 * K2); y1 = y0 + K2 * (x1 - x0); }
    Delta = pii(-x1, -y1);
}

inline void Insert(int x)
{
    double theta = atan2(a[x].point.y, a[x].point.x);
    pii t = pii(sin(theta), cos(theta));
    Modify(Root, -INF, INF, t * sqrt(1.0 * a[x].r));
}

inline bool Query(pii x)
{
    if ( x.y < -eps ) return false;
    double theta = atan2(x.y, x.x);
    // cout << x.x << " " << x.y << " " << theta << endl;
    double x0 = cos(theta), y0 = sin(theta);
    double len = Dis(x), Min = 2 * Query(Root, -INF, INF, x.x / x.y) * y0;
    // cout << y0 << " " << Query(Root, -INF, INF, x.x / x.y) << endl;
    // printf("%.12Lf %.12Lf\n", Min, len);
    return Min > len - eps;

    REP(i, 1, n) 
    {
        double the = atan2(a[i].point.y, a[i].point.x);
        pii t = pii(sin(the), cos(the));
        t = t * sqrt(1.0 * a[i].r);
        Min = min(Min, 2 * f(t, x0 / y0) * y0);
        cout << f(t, x0 / y0) << endl;
        continue ; 
        double theta1 = atan2(x.y, x.x), theta2 = atan2(a[i].point.y, a[i].point.x);
        double theta = theta1 - theta2;
        cout << cos(theta) << " " << 2 * sqrt(1.0 * a[i].r) * cos(theta) << endl;
        Min = min(Min, 2 * sqrt(1.0 * a[i].r) * cos(theta));
    }
    return Min > len - eps;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &q);
    REP(i, 1, 3) scanf("%lld%Lf%Lf%lld", &a[i].r, &a[i].point.x, &a[i].point.y, &a[i].r);    
    Solve(a[1], a[2]);
    theta = atan(1.0 / calc(a[1].point));
    REP(i, 1, 3) { a[i].point = a[i].point + Delta; Change(a[i].point); }
    if ( a[1].point.y < -eps ) 
    { 
        theta += pi; 
        REP(i, 1, 3) { a[i].point.x = -a[i].point.x; a[i].point.y = -a[i].point.y; }
    }
    // REP(i, 1, 3) cout << a[i].point.x << " " << a[i].point.y << endl;
    REP(i, 1, 3) Insert(i);
    bool lstans = false;
    while ( q > 3 ) 
    {
        int op; scanf("%lld", &op);
        if ( op == 1 ) 
        {
            ++ n; scanf("%Lf%Lf%lld", &a[n].point.x, &a[n].point.y, &a[n].r);
            if ( lstans ) swap(a[n].point.x, a[n].point.y);
            a[n].point = a[n].point + Delta; Change(a[n].point); Insert(n);
        }
        else 
        {
            pii point; scanf("%Lf%Lf", &point.x, &point.y);
            if ( lstans ) swap(point.x, point.y); point = point + Delta;
            Change(point); lstans = Query(point); 
            printf("%lld\n", lstans);
        }
        -- q;
    }
    return 0;
}
