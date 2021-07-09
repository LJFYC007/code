/***************************************************************
	File name: canal.cpp
	Author: ljfcnyali
	Create time: 2019年08月11日 星期日 08时58分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define x1 X1
#define x2 X2
#define y1 Y1
#define y2 Y2

typedef long long LL;

const int maxn = 600010;
const int maxm = 2400010;

LL n, m, x1, x2, y1[maxn], y2[maxn], k, f[2 * maxn], s;
double ans;

struct node
{
    int u, v;
    double w;
    bool operator < (const node &a) const { return w < a.w; } 
} a[maxm];

inline double js(int i, int j) { return sqrt((double)(y1[i] - y2[j]) * (y1[i] - y2[j]) + (x1 - x2) * (x1 - x2)); }

inline int cha(int x) { return x == f[x] ? x : f[x] = cha(f[x]); }

int main()
{
    freopen("canal.in", "r", stdin);
    freopen("canal.out", "w", stdout);
    scanf("%lld%lld%lld%lld", &n, &m, &x1, &x2);
    scanf("%lld", &y1[1]);
    REP(i, 2, n) 
    { 
        LL x; scanf("%lld", &x); y1[i] = y1[i - 1] + x;
        a[++ k].u = i - 1; a[k].v = i; a[k].w = x;
    }
    scanf("%lld", &y2[1]);
    REP(i, 2, m) 
    { 
        LL x; scanf("%lld", &x); y2[i] = y2[i - 1] + x; 
        a[++ k].u = n + i - 1; a[k].v = n + i; a[k].w = x;
    }
    REP(i, 1, n)
    {
        int x = lower_bound(y2 + 1, y2 + m + 1, y1[i]) - y2;
        if ( x > m ) x = m; if ( x == 1 ) x = 2;
        a[++ k].u = i; a[k].v = n + x; a[k].w = js(i, x);
        a[++ k].u = i; a[k].v = n + x - 1; a[k].w = js(i, x - 1);
    }
    sort(a + 1, a + k + 1);
    REP(i, 1, n + m) f[i] = i;
    int x = n + m - 1;
    REP(i, 1, k)
    {
        int fx = cha(a[i].u), fy = cha(a[i].v);
        if ( fx != fy ) 
        {
            ++ s; ans += a[i].w;
            f[fx] = fy;
            if ( s == x ) { printf("%.2lf\n", ans); return 0; }
        }
    }
    return 0; 
}
