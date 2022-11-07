/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年09月21日 星期六 15时36分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

int T, n, ans;
int k[20];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &T);
    k[0] = 1; REP(i, 1, 19) k[i] = k[i - 1] * 10;
    while ( T -- ) 
    {
        scanf("%lld", &n); ans = 0;
        int i, x = 0, p = 0, last = 0;
        for ( i = 1; i <= n; i += p ) 
        {
            ++ x;
            int t = x, sum = 0;
            while ( t ) 
            {
                t /= 10; ++ sum;
            }
            last = sum;
            p += sum;
        }
        i -= p;
        // cerr << p << " " << i << endl;
        p = 1;
        while ( i <= n ) 
        {
            x = p ++;
            for ( int j = 10; j >= 0 && i <= n; -- j ) 
            {
                // cerr << x << " " << k[j] << endl;
                if ( x / k[j] == 0 ) continue ;
                ans = x / k[j] % 10;
                // cerr << ans << endl;
                ++ i;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
