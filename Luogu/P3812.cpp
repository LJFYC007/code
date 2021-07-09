/***************************************************************
	File name: P3812.cpp
	Author: ljfcnyali
	Create time: 2019年08月30日 星期五 10时53分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 60;

int n, p[maxn], ans, m[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    m[0] = 1; REP(i, 1, 51) m[i] = m[i - 1] * 2;
    REP(i, 1, n)
    {
        int x; scanf("%lld", &x);
        for ( int j = 51; j >= 0; -- j ) 
        {
            if ( !(m[j] & x) ) continue ;
            if ( !p[j] ) { p[j] = x; break ; }
            x ^= p[j];
        }
    }
    for ( int i = 52; i >= 0; -- i ) if ( (ans ^ m[i]) > ans ) ans ^= p[i];
    printf("%lld\n", ans);
    return 0;
}
