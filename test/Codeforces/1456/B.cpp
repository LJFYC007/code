/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年11月29日 星期日 15时18分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, a[maxn], ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    if ( n >= 100 ) { printf("1\n"); return 0; }
    int ans = n + 1;
    REP(i, 1, n) REP(j, i + 1, n)  
    {
        int val = 0;
        REP(k, i, j) val ^= a[k];

        int x = 0;
        for ( int t = i - 1; t >= 1; -- t ) 
        {
            x ^= a[t];
            if ( x > val ) ans = min(ans, j - t - 1);
        }

        x = 0;
        for ( int t = j + 1; t <= n; ++ t ) 
        {
            x ^= a[t];
            if ( x < val ) ans = min(ans, t - i - 1);
        }
    }
    if ( ans == n + 1 ) puts("-1");
    else printf("%d\n", ans);
    return 0;
}
