/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年07月31日 星期五 08时08分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;

int a[maxn], Mod;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    int T; scanf("%lld%lld", &T, &Mod);
    a[0] = a[1] = 1; a[2] = 2; 
    REP(n, 3, maxn - 10)
    {
        int x = ((10 * n * n + 2 * n - 3) % Mod) * a[n - 1] % Mod;
        int y = (9 * (n - 1) * (n - 1) % Mod) * a[n - 2] % Mod;
        a[n] = (x - y) * power((n + 2) * (n + 2) % Mod, Mod - 2) % Mod;
    }
    while ( T -- ) 
    {
        int n; scanf("%lld", &n);
        printf("%lld\n", (a[n] + Mod) % Mod); 
    }
    return 0;
}
