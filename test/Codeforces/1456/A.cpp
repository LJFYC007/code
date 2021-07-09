/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年11月29日 星期日 15时04分00秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, T, a[maxn], k, p, x, y, ans, b[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &T);
    while ( T -- )
    {
        scanf("%d%d%d", &n, &p, &k);
        REP(i, 1, n) scanf("%1d", &a[i]); 
        scanf("%d%d", &x, &y);
        REP(i, 0, k - 1) b[i] = 0;
        ans = 2147483647;
        for ( int i = n; i >= p; -- i )
        {
            if ( !a[i] ) ++ b[i % k];
            int ret = b[i % k] * x + y * (i - p);
            ans = min(ans, ret);
        }
        printf("%d\n", ans);
    }
    return 0;
}
