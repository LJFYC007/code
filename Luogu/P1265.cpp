/***************************************************************
	File name: P1265.cpp
	Author: ljfcnyali
	Create time: 2019年06月12日 星期三 15时55分01秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 5010;

struct node
{
    LL x, y;
} a[maxn];

int n;
LL dis[maxn];
double ans;
bool vis[maxn];

inline LL js(int s, int t)
{
    return ((a[s].x - a[t].x) * (a[s].x - a[t].x) + (a[s].y - a[t].y) * (a[s].y - a[t].y));
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) scanf("%lld%lld", &a[i].x, &a[i].y);
    vis[1] = true;
    REP(i, 2, n) dis[i] = js(1, i);
    REP(i, 1, n - 1)
    {
        LL Min = 1000000000000ll, x;
        REP(j, 1, n) 
            if ( !vis[j] && dis[j] < Min ) { Min = dis[j]; x = j; }
        vis[x] = true; ans += sqrt(dis[x]);
        REP(j, 1, n)
            if ( !vis[j] ) dis[j] = min(dis[j], js(x, j));
    }
    printf("%.2lf\n", ans);
    return 0;
}
