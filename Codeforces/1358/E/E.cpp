/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2020年05月27日 星期三 08时50分55秒
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
const int INF = 1e18;

int n, m, k, a[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n); m = ceil(n / 2.0);
    REP(i, 1, m) scanf("%lld", &a[i]);
    scanf("%lld", &k);
    int num = k * (n - m);
    a[m] += num;
    REP(i, 1, m - 1) a[i] -= k; 
    for ( int i = m; i >= 1; -- i ) a[i] += a[i + 1];
    REP(i, 2, m) a[i] = min(a[i], a[i - 1]);
    REP(i, 1, m) if ( a[i] + k * (m - i) > 0 ) { printf("%lld\n", n - i + 1); return 0; }
    puts("-1");
    return 0;
}
