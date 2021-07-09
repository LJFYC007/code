/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年06月26日 星期三 10时34分50秒
***************************************************************/
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#include<map>
#include<stack>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 30010;

int dp[110][1130][1130], n, m, a[maxn], p[maxn], num[maxn], cnt, ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    char c;
    REP(i, 1, n)
        REP(j, 1, m) 
        {
            cin >> c;
            if ( c == 'H' ) a[i] += 1 << (j - 1);
        }
    int nn = 1 << m;
    REP(i, 0, nn - 1)
    {
        if ( (i & (i << 1)) || (i & (i << 2)) ) continue ;
        p[++ cnt] = i;
        int x = i;
        while ( x ) 
        {
            if ( x & 1 ) ++ num[cnt];
            x >>= 1;
        }
    }
    REP(i, 1, cnt)
        REP(j, 1, cnt)
            if ( !(p[i] & p[j]) && !(p[i] & a[2]) && !(p[j] & a[1]) )
                dp[2][i][j] += num[i] + num[j];
    REP(i, 3, n)
        REP(j, 1, cnt)
        {
            if ( p[j] & a[i] ) continue ;
            REP(k, 1, cnt)
            {
                if ( (p[k] & a[i - 1]) || (p[k] & p[j]) ) continue ;
                REP(o, 1, cnt)
                {
                    if ( (p[o] & a[i - 2]) || (p[o] & p[k]) || (p[o] & p[j]) ) continue ;
                    dp[i][j][k] = max(dp[i][j][k], dp[i - 1][k][o] + num[j]);
                    ans = max(ans, dp[i][j][k]);
                }
            }
        }
    printf("%d\n", ans);
    return 0;
}
