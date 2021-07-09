/***************************************************************
	File name: CF891E.cpp
	Author: ljfcnyali
	Create time: 2020年06月10日 星期三 15时31分56秒
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
const int Mod = 1e9 + 7;

int n, k, a[maxn], ans, fac[maxn], inv[maxn], b[maxn], c[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void Mul(int x, int y)
{
    for ( int i = n; i >= 1; -- i ) b[i] = (b[i] * x + y * b[i - 1]) % Mod;
    b[0] = x * b[0] % Mod;
}

inline int Get(int l, int r)
{
    int ret = 1;
    REP(i, r, l) ret = ret * i % Mod;
    return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &k);
    REP(i, 1, n) scanf("%lld", &a[i]);
    ans = 1; REP(i, 1, n) ans = ans * a[i] % Mod;
    b[0] = 1;
    REP(i, 1, n) Mul(a[i], -1);
    int sum = 0;
    REP(i, 0, min(n + 10, k)) sum = (sum + (power(n, k - i) * Get(k, k - i + 1) % Mod) * b[i]) % Mod;
    sum = sum * power(power(n, k), Mod - 2) % Mod;
    ans = (ans - sum) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
