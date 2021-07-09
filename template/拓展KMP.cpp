/***************************************************************
	File name: 拓展KMP.cpp
	Author: ljfcnyali
	Create time: 2020年08月13日 星期四 15时30分24秒
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

int n, m, f[maxn], g[maxn], ans;
char s[maxn], t[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s + 1); n = str(s + 1);
    scanf("%s", t + 1); m = str(t + 1);
    int l = 0, r = 0; g[1] = m;
    REP(i, 2, m)
    {
        if ( i <= r ) g[i] = min(r - i + 1, g[i - l + 1]);
        while ( i + g[i] <= m && t[g[i] + 1] == t[i + g[i]] ) ++ g[i];
        if ( i + g[i] - 1 >= r ) { r = i + g[i] - 1; l = i; }
    }
    REP(i, 1, m) ans ^= i * (g[i] + 1);
    printf("%lld\n", ans);

    l = 0; r = 0;
    REP(i, 1, n)
    {
        if ( i <= r ) f[i] = min(r - i + 1, g[i - l + 1]);
        while ( i + f[i] <= n && f[i] < m && t[f[i] + 1] == s[i + f[i]] ) ++ f[i];
        if ( i + f[i] - 1 >= r ) { r = i + f[i] - 1; l = i; }
    }
    ans = 0; REP(i, 1, n) ans ^= i * (f[i] + 1); printf("%lld\n", ans);
    return 0;
}

