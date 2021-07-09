/***************************************************************
	File name: square.cpp
	Author: ljfcnyali
	Create time: 2020年09月02日 星期三 19时24分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 19260817;

int T, n, ans;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
    freopen("square.in", "r", stdin);
    freopen("square1.out", "w", stdout);
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld", &n); ans = 1;
        REP(i, 1, n) REP(j, 1, n) ans = ans * (i * j % Mod) % Mod;
        REP(i, 1, n) REP(j, 1, n)
        {
            int x = power(__gcd(i, j), Mod - 2);
            ans = ans * (x * x % Mod) % Mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
