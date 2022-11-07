/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年04月13日 星期一 21时33分46秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;

int T, n, a[maxn], ans;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%I64d", &T);
    while ( T -- ) 
    {
        scanf("%I64d", &n);
        REP(i, 1, n) scanf("%I64d", &a[i]);
        ans = 0;
        REP(i, 2, n)
        {
            if ( a[i] >= a[i - 1] ) continue ;
            int x = a[i - 1] - a[i];
            a[i] += x;
            for ( int j = 30; j >= 0; -- j ) if ( (x >> j) & 1 ) { ans = max(ans, j + 1); break ; }
        }
        printf("%I64d\n", ans);
    }
    return 0;
}
