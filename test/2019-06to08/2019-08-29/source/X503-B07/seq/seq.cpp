/***************************************************************
	File name: seq.cpp
	Author: ljfcnyali
	Create time: 2019年08月29日 星期四 09时24分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 1000010;

int a[maxn], n, Last[32], f[maxn], ans;

signed main()
{
    freopen("seq.in", "r", stdin);
    freopen("seq.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, n)
    {
        REP(j, 0, 30) 
        {
            if ( !((1LL << j) & a[i]) ) continue ;
            f[i] = max(f[i], f[Last[j]] + 1);
            Last[j] = i;
        }
    }
    REP(i, 1, n) ans = max(ans, f[i]);
    printf("%lld\n", ans);
    return 0;
}
