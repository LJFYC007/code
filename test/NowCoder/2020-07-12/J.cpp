/***************************************************************
	File name: J.cpp
	Author: ljfcnyali
	Create time: 2020年07月12日 星期日 12时28分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 998244353;

int f[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int p = 4, q = 3, x = 1;
    f[1] = p * power(q, Mod - 2) % Mod;
    REP(i, 2, maxn - 10)
    {
        p = p * 2 % Mod;
        q = q * (2 * i + 1) % Mod;
        x = x * i % Mod;
        f[i] = p * power(q, Mod - 2) % Mod;
        f[i] = f[i] * x % Mod;
    }
    REP(i, 1, maxn - 10) f[i] = f[i] * power(power(2, 1 + 2 * i), Mod - 2) % Mod;
    int n;
    while ( ~scanf("%lld", &n) )
    {
        printf("%lld\n", (f[n] + Mod) % Mod);
    }
    return 0;
}
