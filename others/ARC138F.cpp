#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef unsigned long long LL;

const LL Mod = 1e9 + 7;

LL L, R, ans;

inline LL Get(LL x)
{
  	if ( x <= 0 ) return 0;
    if ( x == 1 ) return 1;
    if ( x == 2 ) return 3;
    if ( x % 2 == 0 ) return (Get(x / 2LL) * 3LL) % Mod;
    LL sum = (Get(x / 2LL) * 3LL) % Mod, y = -1;
    REP(i, 0, 63) if ( (x >> i) & 1LL ) ++ y; 
    if ( y == -1 ) return sum;
    return (sum + ((1LL << y) % Mod)) % Mod;
}

int main()
{
    cin >> L >> R;
    LL x = 1, sum = 1;
    while ( x * 2 < L ) 
    {
        x *= 2; sum = (sum * 3LL) % Mod;       
    }
    if ( x <= L && R < x * 2 )
    {
        REP(i, L, R) REP(j, i, R) if ( j % i == (j ^ i) ) ++ ans;
        // ans = Get(x * 2 - R + 1) - Get(x * 2 - L);
        // ans = ((ans % Mod) + Mod) % Mod;
        cout << ans % Mod << endl; return 0;
    }
    x *= 2;
    ans += Get(x - L);
    while ( x * 2 - 1 <= R ) 
    {
        x *= 2; 
        sum = (sum * 3LL) % Mod;
        ans = (ans + sum) % Mod;
    }
    ans = (ans + Get(R - x + 1)) % Mod;
    cout << ans << endl;
    return 0;
}

