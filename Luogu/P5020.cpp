/***************************************************************
	File name: P5020.cpp
	Author: ljfcnyali
	Create time: 2019年06月07日 星期五 15时20分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 300010;

int dp[maxn], T, n, a[maxn], ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &T);    
    while ( T -- ) 
    {
        scanf("%d", &n);
        REP(i, 1, n) scanf("%d", &a[i]);
        sort ( a + 1, a + n + 1 );
        mem(dp); dp[0] = 1; ans = n;
        REP(i, 1, n)
        {
            if ( dp[a[i]] ) -- ans;        
            REP(j, a[i], a[n])
                if ( dp[j - a[i]] ) dp[j] = 1;
        }   
        printf("%d\n", ans);
    }
    return 0;
}
