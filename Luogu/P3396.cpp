/***************************************************************
	File name: P3396.cpp
	Author: ljfcnyali
	Create time: 2019年08月06日 星期二 14时08分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 300010;

int n, block, m, a[maxn], p[4010][4010];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    block = sqrt(n);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, block)
        REP(j, 1, n)
            p[i][j % i] += a[j];
    REP(i, 1, m)
    {
        char s[10]; int x, y;
        scanf("%s %d%d", s, &x, &y);
        if ( s[0] == 'A' ) 
        {
            if ( x <= block ) { printf("%d\n", p[x][y]); continue ; }
            int ans = 0;
            for ( int j = y; j <= n; j += x ) ans += a[j];
            printf("%d\n", ans);
        }
        else
        {
            REP(i, 1, block) p[i][x % i] = p[i][x % i] - a[x] + y;
            a[x] = y;
        }
    }
    return 0;
}
