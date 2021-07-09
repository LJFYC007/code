/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年11月01日 星期日 19时02分57秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

int NNN;

inline int Check(int n, int x)
{
    while ( n % NNN == 0 ) n /= x;
    return n;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T, p, q; scanf("%lld", &T);
    while ( T -- ) 
    {
        cin >> p >> q;
        if ( p % q != 0 ) printf("%lld\n", p);
        else 
        {
            NNN = q;
            int ans = 0;
            for ( int i = 2; i * i <= q; ++ i )
            {
                if ( q % i == 0 ) ans = max(ans, Check(p, i));
                while ( q % i == 0 ) q /= i;
            }
            if ( q > 1 ) ans = max(ans, Check(p, q));
            printf("%lld\n", ans);
        }
    }
    return 0;
}
