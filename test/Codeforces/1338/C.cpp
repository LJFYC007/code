/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年04月14日 星期二 12时55分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 110;
const int INF = 1e18;

int T, n, m;
pii a[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%I64d", &T);
    int sum1 = 1, sum2 = 1;
    REP(i, 1, 30)
    {
        a[++ m] = pii(sum1, sum2);
        sum1 += 1ll << i + i - 2;
        sum2 = 1ll << i + i;
    }
    while ( T -- ) 
    {
        scanf("%I64d", &n);
        int line = (n + 2) / 3;
        int pos = upper_bound(a + 1, a + m + 1, pii(line, INF)) - a - 1;
        int x = a[pos].second + (line - a[pos].first);
        int y = 0;
        line -= a[pos].first;
        REP(i, 1, 30)
        {
            int val = 0;
            if ( line % 4 == 1 ) val = 2;
            else if ( line % 4 == 2 ) val = 3;
            else if ( line % 4 == 3 ) val = 1;
            y |= val << (i + i - 2);
            line /= 4;
        }
        y += a[pos].second * 2;
        int z = x ^ y;
        if ( n % 3 == 1 ) printf("%I64d\n", x);
        else if ( n % 3 == 2 ) printf("%I64d\n", y);
        else printf("%I64d\n", z);
    }
    return 0;
}
