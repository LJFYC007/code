/***************************************************************
	File name: farm.cpp
	Author: ljfcnyali
	Create time: 2020年01月18日 星期六 09时12分57秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 30;

int w, h, n, a[maxn][maxn], ans;

int main()
{
    freopen("farm.in", "r", stdin);
    freopen("farm.out", "w", stdout);
    scanf("%d%d%d", &w, &h, &n);
    REP(i, 1, n) { int x, y; scanf("%d%d", &x, &y); a[x][y] = 1; }
    REP(x1, 0, w) REP(y1, 0, h) REP(x2, x1 + 1, w) REP(y2, y1 + 1, h)
    {
        bool flag = true;
        REP(i, x1 + 1, x2 - 1) REP(j, y1 + 1, y2 - 1) if ( a[i][j] ) flag = false;
        if ( flag ) ans = max(ans, (x2 - x1 + y2 - y1) * 2);
    }
    printf("%d\n", ans);
    return 0;
}
