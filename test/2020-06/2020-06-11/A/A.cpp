/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年06月11日 星期四 11时41分53秒
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
const int Mod = 998244353;

int n, m, a[maxn][40], l, r, x, ans;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) 
    {
        int x; scanf("%lld", &x); 
        REP(j, 0, 31) a[i][j] = a[i - 1][j] + ((x >> j) & 1);
    }
    REP(i, 1, m)
    {
        int l, r, x; scanf("%lld%lld%lld", &l, &r, &x);
        int ans = 0;
        REP(j, 0, 31)
        {
            int n = a[r][j] - a[l - 1][j];
            int m = r - l + 1 - n;
            int sum = (power(x + 1, n) - power(1 - x, n)) * ((Mod + 1) / 2) % Mod;;
            sum = sum * power(x + 1, m) % Mod;
            sum = sum * (1 << j) % Mod;
            ans = (ans + sum) % Mod;
        }
        printf("%lld\n", (ans + Mod) % Mod);
    }
    return 0;
}
