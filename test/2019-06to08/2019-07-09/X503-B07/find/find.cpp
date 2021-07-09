/***************************************************************
	File name: find.cpp
	Author: ljfcnyali
	Create time: 2019年07月09日 星期二 08时39分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;

struct node
{
    int x, y;
} b[maxn];

int n, cnt, a[maxn], tot;

inline int cmp(node a, node b)
{
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

int main()
{
    freopen("find.in", "r", stdin);
    freopen("find.out", "w", stdout);
    scanf("%d", &n); 
    REP(i, 1, n)
    {
        int x, y; scanf("%d%d", &x, &y);
        if ( x < 0 || y < 0 ) continue ; 
        b[++ cnt].x = x; b[cnt].y = y;
    }
    sort(b + 1, b + cnt + 1, cmp);
    a[++ tot] = b[1].y;
    REP(i, 2, cnt)
    {
        if ( b[i].y >= a[tot] ) { a[++ tot] = b[i].y; continue ; } 
        if ( b[i].y < a[1] ) { a[1] = b[i].y; continue ; } 
        int l = 1, r = tot, pos;
        while ( l <= r ) 
        {
            int Mid = l + r >> 1;
            if ( a[Mid] > b[i].y ) { pos = Mid; r = Mid - 1; }
            else l = Mid + 1;
        }
        a[pos] = b[i].y;
    }
    printf("%d\n", tot);
    return 0;
}

