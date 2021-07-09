/***************************************************************
	File name: chess.cpp
	Author: ljfcnyali
	Create time: 2020年01月19日 星期日 08时35分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;

int n, k, ret;
struct point { int x, y; } a[maxn];
map<int, map<int, bool> > Map;

inline bool Check(int x, int y)
{
    int sum = 0, L = 1, R = n;
    // printf("%lld %lld\n", x, y);
    while ( L <= R ) 
    {
        // printf("%lld %lld %lld\n", L, R, sum);
        // printf("%lld %lld %lld %lld\n", a[L].x, a[L].y, a[R].x, a[R].y);
        if ( sum > k ) return false;
        if ( L == R && a[L].x == x && a[L].y == y ) return true;
        if ( L == R ) ++ sum;
        if ( sum > k ) return false;
        if ( L == R ) break ;
        if ( a[L].x + a[R].x == x * 2 )
        {
            if ( a[L].y + a[R].y == y * 2 ) { ++ L; -- R; }
            else
            {
                ++ sum;
                if ( y - a[L].y > a[R].y - y ) ++ L; else -- R;
            }
        }
        else 
        { 
            ++ sum;
            if ( x - a[L].x > a[R].x - x ) ++ L; else -- R;
        }
    }
    // printf("%lld %lld\n", x, y);
    return true;
}

signed main()
{
    freopen("chess.in", "r", stdin);
    freopen("chess.out", "w", stdout);
    scanf("%lld%lld", &n, &k);
    REP(i, 1, n) { scanf("%lld%lld", &a[i].x, &a[i].y); a[i].x *= 2; a[i].y *= 2; }
    if ( k >= n ) { puts("-1"); return 0; }  
    sort(a + 1, a + n + 1, [](point &a, point &b) { return a.x < b.x || (a.x == b.x && a.y < b.y); });
    REP(i, 1, min(25ll, n)) REP(j, max(i + 1, n - 25), n) 
    {
        int x = (a[i].x + a[j].x) / 2, y = (a[i].y + a[j].y) / 2;
        if ( Map[x][y] ) continue ; Map[x][y] = true;
        if ( Check(x, y) ) ++ ret;
    } 
    printf("%lld\n", ret);
    return 0;
}
