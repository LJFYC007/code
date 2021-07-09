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

const int maxn = 4010;

int n, k, ret;
struct point { int x, y; } a[maxn];
map<int, map<int, bool> > Map, Ans;

signed main()
{
    freopen("chess.in", "r", stdin);
    freopen("chess.out", "w", stdout);
    scanf("%lld%lld", &n, &k);
    REP(i, 1, n) { scanf("%lld%lld", &a[i].x, &a[i].y); a[i].x *= 2; a[i].y *= 2; Map[a[i].x][a[i].y] = true; }
    if ( k >= n ) { puts("-1"); return 0; }  
    REP(i, 1, n) REP(j, i + 1, n)
    {
        int sum = 0, x = (a[i].x + a[j].x) / 2, y = (a[i].y + a[j].y) / 2;
        if ( Ans[x][y] ) continue ;
        REP(o, 1, n)  
        {
            int X = 2 * x - a[o].x, Y = 2 * y - a[o].y;
            if ( !Map[X][Y] ) ++ sum;
        }
        Ans[x][y] = true;
        if ( sum <= k ) ++ ret;
    }
    printf("%lld\n", ret);
    return 0;
}
