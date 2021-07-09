/***************************************************************
	File name: P2145.cpp
	Author: ljfcnyali
	Create time: 2019年06月26日 星期三 08时34分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 5010;

int f[maxn][maxn], n, a[maxn], sum[maxn], m;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &m);
    REP(i, 1, m)
    {
        scanf("%d", &a[i]);
        if ( a[i] == a[i - 1] ) ++ sum[n];
        else { sum[++ n] = 1; a[n] = a[i]; }
    }
    memset(f, 0x3f, sizeof(f));
    REP(i, 1, n) if ( sum[i] >= 2 ) f[i][i] = 1; else f[i][i] = 2;
    REP(len, 2, n)
        REP(i, 1, n)
        {
            int j = i + len - 1;
            if ( j > n ) break ;
            if ( a[i] == a[j] ) 
            {
                if ( sum[i] + sum[j] > 2 ) f[i][j] = min(f[i][j], f[i + 1][j - 1]);
                else f[i][j] = min(f[i][j], f[i + 1][j - 1] + 1);
            }
            else REP(k, i, j - 1) f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
        }
    printf("%d\n", f[1][n]);
    return 0;
}
