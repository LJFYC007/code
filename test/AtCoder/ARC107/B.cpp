/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年10月31日 星期六 20时03分32秒
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

int n, k, ans;

inline int Solve(int x)
{
    int l = x - n, r = x - 1;
    l = max(l, 1ll); r = min(n, r);
    if ( l <= r ) return r - l + 1;
    return 0;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin >> n >> k;
    REP(i, 2, n * 2)
    {
        int val1 = i, val2 = i - k;
        ans += Solve(val1) * Solve(val2);
    }
    printf("%lld\n", ans);
    return 0;
}
