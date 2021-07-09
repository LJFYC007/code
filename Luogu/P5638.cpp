/***************************************************************
	File name: P5638.cpp
	Author: ljfcnyali
	Create time: 2019年11月10日 星期日 19时02分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1000010;

int n, k, a[maxn], ans;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &k);
    REP(i, 1, n - 1) { scanf("%lld", &a[i]); a[i] += a[i - 1]; }
    REP(i, 1, n - 1) ans = max(ans, a[i] - a[max(0ll, i - k)]);
    printf("%lld\n", a[n - 1] - ans);
    return 0;
}
