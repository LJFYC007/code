/***************************************************************
	File name: AtCoderAGC040F.cpp
	Author: ljfcnyali
	Create time: 2020年06月07日 星期日 09时53分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e7 + 10;
const int Mod = 998244353;

int ans, n, a, b, X, Y, fac[maxn], inv[maxn];

inline int power(int a, int b){ int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

inline int Get(int x, int y)
{
    return C(x + y - 1, x - 1) - C(x + y - 1, y - 1);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = maxn - 10;
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld%lld%lld", &n, &a, &b); 
    if ( a == 0 && b == 0 ) { puts("1"); return 0; }
    X = b; Y = b - a;    
    if ( X + (X - Y) == n ) ans = Get(X, X - Y);
    REP(i, 1, n)
    {
        b = n - i - X;
        if ( b < 0 ) break ;
        int H = X - b;
        if ( H < Y ) continue ;
        H -= Y;
        int num = Get(X, b);
        ans = (ans + num * C(H + i - 1, i - 1)) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
