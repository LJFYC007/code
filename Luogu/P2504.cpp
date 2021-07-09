/***************************************************************
	File name: P2504.cpp
	Author: ljfcnyali
	Create time: 2019年06月24日 星期一 19时43分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;

int a[maxn], b[maxn], n, m, x[maxn], ans, cnt, f[maxn], sum;
struct node
{
    int u, v;
    double w;
} p[maxn];

inline double js(int x, int y)
{
    return sqrt((double)(a[x] - a[y]) * (a[x] - a[y]) + (b[x] - b[y]) * (b[x] - b[y]));
}

inline int cmp(node a, node b)
{
    return a.w < b.w;
}

inline int cha(int x) { return x == f[x] ? x : f[x] = cha(f[x]); }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &m); 
    REP(i, 1, m) scanf("%d", &x[i]);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d%d", &a[i], &b[i]);
    REP(i, 1, n - 1)
        REP(j, i + 1, n)
        {
            p[++ cnt].u = i; p[cnt].v = j;
            p[cnt].w = js(i, j);
        }
    sort(p + 1, p + cnt + 1, cmp);
    REP(i, 1, n) f[i] = i;
    REP(i, 1, cnt)
    {
        int fx = cha(p[i].u), fy = cha(p[i].v);
        if ( fx != fy ) 
        {
            f[fx] = fy;
            ++ sum;
        }
        if ( sum == n - 1 )
        {
            REP(j, 1, m) if ( x[j] >= p[i].w ) ++ ans;
            printf("%d\n", ans); return 0;
        }
    }
    return 0;
}
