/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年11月29日 星期日 15时37分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5e5 + 10;

int n, k, a[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &k);
    REP(i, 1, n) scanf("%lld", &a[i]);
    sort(a + 1, a + n + 1);
    int sum = 0, ans = 0, now = n;
    while ( now >= 1 && sum >= 0 ) { ans += sum; sum += a[now]; -- now; }

    a[++ now] = sum; n = now;
    // REP(i, 1, n) cout << a[i] << " "; cout << endl;
    REP(o, 1, k + 1)
    {
        int x = now; -- now; sum = 0; 
        while ( x >= 1 ) { ans += sum; sum += a[x]; x -= k + 1; }
    }
    printf("%lld\n", ans);
    return 0;
}
