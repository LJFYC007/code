/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年10月11日 星期日 17时09分41秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;

int T, a[maxn], n, k;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld", &n, &k);
        REP(i, 1, n) scanf("%lld", &a[i]);
        sort(a + 1, a + n + 1); reverse(a + 1, a + n + 1);
        int now = 2;
        while ( k && now <= n ) 
        {
            a[1] += a[now]; a[now] = 0; 
            -- k; ++ now;
        }
        sort(a + 1, a + n + 1);
        printf("%lld\n", a[n] - a[1]);
    }
    return 0;
}
