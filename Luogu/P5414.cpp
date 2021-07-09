/***************************************************************
	File name: P5414.cpp
	Author: ljfcnyali
	Create time: 2019年06月09日 星期日 10时12分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 110;

int T, n, a[maxn], dp[maxn], sum, Max;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &T);    
    while ( T -- ) 
    {
        scanf("%d", &n); sum = 0; Max = 0;
        REP(i, 1, n) { scanf("%d", &a[i]); sum += a[i]; }
        REP(i, 1, n)
        {
            dp[i] = a[i];
            REP(j, 1, i - 1)
                if ( a[j] <= a[i] ) dp[i] = max(dp[i], dp[j] + a[i]);
            Max = max(Max, dp[i]);
        }
        printf("%d\n", sum - Max);
    }
    return 0;
}
