/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年11月04日 星期一 21时07分28秒
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

int T, n, m;
char a[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld", &n, &m);
        scanf("%s", a + 1);
        int s = 1, t = 1;
        while ( m ) 
        {
            while ( s <= n && a[s] == '0' ) ++ s;
            t = max(t, s + 1);
            while ( t <= n && a[t] == '1' ) ++ t;
            if ( t > n ) break ; 
            if ( t - s <= m ) { m -= t - s; a[s] = '0'; a[t] = '1'; ++ s; ++ t; }
            else { int x = t - m; a[x] = '0'; a[t] = '1'; break ; }
        }
        printf("%s\n", a + 1);
    }
    return 0;
}
