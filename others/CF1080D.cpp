/***************************************************************
	File name: CF1080D.cpp
	Author: ljfcnyali
	Create time: 2019年09月27日 星期五 08时30分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

int n, T, k, p[31];

inline int power(int a, int b)
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r *= a; a *= a; b >>= 1; }
    return r;
}


signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    REP(i, 0, 30) p[i] = p[i - 1] + power(2, 2 * i);
    scanf("%I64d", &T);
    while ( T -- ) 
    {
        scanf("%I64d%I64d", &n, &k);
        if ( n == 2 && k == 3 ) { puts("NO"); continue ; }
        if ( n > 31 ) { printf("YES %I64d\n", n - 1); continue ; }
        int L = 0, y = 1, R = 0, x = 2, num = 1;
        for ( int i = n - 1; i >= 0; -- i )
        {
            L += y; R += num * p[i - 1];
            y += x; x *= 2; num += x;
            // cerr << L << " " << L + R << endl;
            if ( L <= k && k <= L + R ) { printf("YES %I64d\n", i); goto finish ; }
        }
        puts("NO");
finish : ; 
    }
    return 0;
}
