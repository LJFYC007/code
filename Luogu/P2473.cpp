/***************************************************************
	File name: P2473.cpp
	Author: ljfcnyali
	Create time: 2019年08月19日 星期一 21时27分06秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 100010;

int K, n;
double dp[110][maxn];

struct node
{
    int val, s;
} a[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &K, &n);
    REP(i, 1, n) 
    { 
        scanf("%d", &a[i].val); 
        int x; scanf("%d", &x);
        while ( x != 0 ) { a[i].s = a[i].s | (1 << x - 1); scanf("%d", &x); }
    }
    int num = 1 << n;
    for ( int i = K; i >= 1; -- i )
        REP(j, 0, num - 1)
        {
            REP(k, 1, n) 
            {
                if ( (j & a[k].s) == a[k].s ) dp[i][j] += max(dp[i + 1][j], dp[i + 1][j | (1 << k - 1)] + a[k].val);
                else dp[i][j] += dp[i + 1][j];
            }
            dp[i][j] = dp[i][j] * 1.0 / n;
        }
    printf("%.6lf", dp[1][0]);
    return 0;
}
