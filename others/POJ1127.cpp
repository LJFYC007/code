/***************************************************************
	File name: POJ1127.cpp
	Author: ljfcnyali
	Create time: 2020年01月12日 星期日 11时02分35秒
***************************************************************/
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
#include<map>
#include<stack>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 110;

int n, f[maxn];
struct Line { pii a, b; } a[maxn];

inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

inline int multi(pii p0, pii p1, pii p2)
{
    return (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x);
}

inline bool Check(int x, int y)
{
    if ( max(a[x].a.x, a[x].b.x) < min(a[y].a.x, a[y].b.x) || max(a[y].a.x, a[y].b.x) < min(a[x].a.x, a[x].b.x) ) return false;
    if ( max(a[x].a.y, a[x].b.y) < min(a[y].a.y, a[y].b.y) || max(a[y].a.y, a[y].b.y) < min(a[x].a.y, a[x].b.y) ) return false;
    if ( multi(a[x].a, a[y].a, a[x].b) * multi(a[x].a, a[x].b, a[y].b) < 0 ) return false;
    if ( multi(a[y].a, a[x].a, a[y].b) * multi(a[y].a, a[y].b, a[x].b) < 0 ) return false;
    return true;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    while ( ~scanf("%d", &n) )
    {
        REP(i, 1, n) f[i] = i;
        REP(i, 1, n) scanf("%d%d%d%d", &a[i].a.x, &a[i].a.y, &a[i].b.x, &a[i].b.y); 
        REP(i, 1, n) REP(j, i + 1, n) if ( Check(i, j) )
        {
            int fx = find(i), fy = find(j);
            if ( fx != fy ) f[fx] = fy;
        }
        int x, y;
        while ( ~scanf("%d%d", &x, &y) )
        {
            if ( x + y == 0 ) break ; 
            int fx = find(x), fy = find(y);
            if ( fx == fy ) puts("CONNECTED");
            else puts("NOT CONNECTED");
        }
    }
    return 0;
}
