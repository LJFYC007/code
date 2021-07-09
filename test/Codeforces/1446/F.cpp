/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2020年11月16日 星期一 18时56分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define pdd pair<double, double>
#define x first
#define y second
typedef long long LL;

const int maxn = 2e5 + 10;
const double eps = 1e-12;
const double pi = acos(-1);

int n, k, c[maxn];
pii a[maxn];
vector<pdd> p;
vector<pii> q;
map<double, int> Map;

inline int lowbit(int x) { return x & -x; }

inline void add(int pos, int val) { for ( int i = pos; i < maxn; i += lowbit(i) ) c[i] += val; }

inline int get(int pos) { int sum = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) sum += c[i]; return sum; }

inline bool InCircle(pii x, double r)
{
    if ( x.x * x.x + x.y * x.y <= r * r + eps ) return true;
    return false;
}

inline pdd Get(pii x, double r)
{
    double theta = atan(x.y * 1.0 / x.x); if ( x.x < 0 ) theta += pi;
    double alpha = acos(r / sqrt((double)x.x * x.x + x.y * x.y));
    double a1 = theta + alpha, a2 = theta - alpha;
    while ( a1 < 0 ) a1 += 2 * pi; while ( a1 > 2 * pi ) a1 -= 2 * pi;
    while ( a2 < 0 ) a2 += 2 * pi; while ( a2 > 2 * pi ) a2 -= 2 * pi;
    Map[a1] = Map[a2] = -1; 
    return pdd(min(a1, a2), max(a1, a2));
}

inline bool Check(double Mid)
{
    int num = k; p.clear(); q.clear(); Map.clear(); mem(c); 
    REP(i, 1, n)  
    {
        if ( InCircle(a[i], Mid) ) continue ;
        p.push_back(Get(a[i], Mid)); 
    }
    int m = 0; for ( auto it : Map ) Map[it.first] = ++ m;
    for ( auto it : p ) q.push_back(pii(Map[it.x], Map[it.y]));
    sort(q.begin(), q.end());

    for ( int i = 0; i < q.size(); ++ i )
    {
        num -= get(q[i].y) - get(q[i].x - 1);
        add(q[i].y, 1);
    }
    return num >= 0; 
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &k); k = n * (n - 1) / 2 - k;
    REP(i, 1, n) scanf("%lld%lld", &a[i].x, &a[i].y);
    double L = 0, R = 20000;
    REP(o, 0, 40)
    {
        double Mid = (L + R) / 2;
        if ( Check(Mid) ) R = Mid;
        else L = Mid;
    }
    printf("%.6lf\n", (L + R) / 2);
    return 0;
}
