/***************************************************************
	File name: P5410.cpp
	Author: ljfcnyali
	Create time: 2020年06月13日 星期六 14时16分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e7 + 10;

int n, m, a[maxn], b[maxn];
char s[maxn], t[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s + 1); n = str(s + 1);
    scanf("%s", t + 1); m = str(t + 1);
    int L = 0, R = 0;
    a[1] = m;
    REP(i, 2, m)
    {
        if ( i <= R ) a[i] = min(R - i + 1, a[i - L + 1]);
        while ( i + a[i] <= m && t[a[i] + 1] == t[i + a[i]] ) ++ a[i];
        if ( i + a[i] - 1 > R ) { L = i; R = i + a[i] - 1; }
    }
    int ans = 0;
    REP(i, 1, m) ans = ans ^ i * (a[i] + 1);
    printf("%lld\n", ans);
    L = R = ans = 0;
    REP(i, 1, n)
    {
        if ( i <= R ) b[i] = min(R - i + 1, a[i - L + 1]);
        while ( i + b[i] <= n && t[b[i] + 1] == s[i + b[i]] ) ++ b[i];
        if ( i + b[i] - 1 > R ) { L = i; R = i + b[i] - 1; }
    }
    REP(i, 1, n) ans = ans ^ i * (b[i] + 1);
    printf("%lld\n", ans);
    return 0;
}

