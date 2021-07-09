/***************************************************************
	File name: chk.cpp
	Author: ljfcnyali
	Create time: 2020年11月23日 星期一 10时04分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int a[210][10010], n, m;

int main()
{
    freopen("color.in", "r", stdin);
    scanf("%d%d", &n, &m); 
    freopen("color.out", "r", stdin);
    REP(i, 1, 2 * n) REP(j, 1, m) scanf("%d", &a[i][j]);
    REP(i, 1, 2 * n) REP(j, 1, m)
        REP(x, i + 1, 2 * n) REP(y, j + 1, m)
            if ( a[i][j] == a[x][y] && a[i][j] == a[i][y] && a[i][j] == a[x][j] )   
            { puts("WA"); cerr << i << " " << j << " " << x << " " << y << " " << a[i][j] << endl; return 0; }
    puts("AC");
    return 0;
}
