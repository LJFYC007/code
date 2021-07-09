/***************************************************************
	File name: P2218.cpp
	Author: ljfcnyali
	Create time: 2019年06月09日 星期日 15时06分03秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 10100;
const int INF = 0x3f3f3f3f;

struct node
{
    int x, y;
} a[maxn];
int n, ans;

inline bool check(int l)
{
    int Minx = INF, Miny = INF, Maxx = -INF, Maxy = -INF;
    int minx = INF, miny = INF, maxx = -INF, maxy = -INF;
    REP(i, 1, n) 
    {
        Minx = min(Minx, a[i].x);
        Miny = min(Miny, a[i].y);
        Maxx = max(Maxx, a[i].x);
        Maxy = max(Maxy, a[i].y);
    }
    REP(i, 1, n)
    {
        if ( Minx <= a[i].x && a[i].x <= Minx + l && Maxy - l <= a[i].y && a[i].y <= Maxy ) continue ;
        if ( Maxx - l <= a[i].x && a[i].x <= Maxx && Miny <= a[i].y && a[i].y <= Miny + l ) continue ;
        minx = min(minx, a[i].x);
        miny = min(miny, a[i].y);
        maxx = max(maxx, a[i].x);
        maxy = max(maxy, a[i].y);
    }
    if ( maxx - minx <= l && maxy - miny <= l ) { ans = l; return true; }
    return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d%d", &a[i].x, &a[i].y);
    int L = 0, R = 100000000;
    while ( L <= R ) 
    {
        int Mid = L + R >> 1;
        if ( check(Mid) ) R = Mid - 1;
        else L = Mid + 1;
    }
    printf("%d\n", ans);
    return 0;
}
