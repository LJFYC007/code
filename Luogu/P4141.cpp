/***************************************************************
	File name: P4141.cpp
	Author: ljfcnyali
	Create time: 2019年09月14日 星期六 10时51分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 2010;

int f[maxn], a[maxn], n, m, g[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    f[0] = 1;
    REP(i, 1, n) 
    {
        scanf("%lld", &a[i]); 
        for ( int j = m; j >= a[i]; -- j ) f[j] = (f[j] + f[j - a[i]]) % 10;
    }
    REP(i, 1, n)
    {
        REP(j, 0, m) g[j] = f[j];
        REP(j, a[i], m) g[j] = ((g[j] - g[j - a[i]]) % 10 + 10) % 10;
        REP(j, 1, m) printf("%lld", g[j] % 10);
        puts("");
    }
    return 0;
}
