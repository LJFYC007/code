/***************************************************************
	File name: map.cpp
	Author: ljfcnyali
	Create time: 2021年01月21日 星期四 10时17分39秒
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

int n, m, a[maxn], b[maxn], ans = 1, fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; } 
inline int sgn(int x) { return x & 1 ? -1 : 1; }

inline int Solve(int n, int m, int x, int y, int w)
{
    int ret = 0;
    REP(i, 0, x) REP(j, 0, y)
    {
        int val = C(x, i) * C(y, j) * sgn(i + j) % Mod;
        int num1 = i * m + j * n - i * j;
        int num2 = x * m + y * n - x * y - num1;
        ret = (ret + val * power(w - 1, num1) % Mod * power(w, num2)) % Mod;
    }
    return ret;
}

signed main()
{
    freopen("map.in", "r", stdin);
    freopen("map.out", "w", stdout);
    n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, m) scanf("%lld", &b[i]);
    sort(a + 1, a + n + 1); sort(b + 1, b + m + 1);

    int X = 1, Y = 1;
    REP(val, 1, 100000)
    {
        int x = X; while ( a[x] == val ) ++ x;
        int y = Y; while ( b[y] == val ) ++ y; 
        int lenx = x - X, leny = y - Y; 
        ans = ans * Solve(n - X + 1, m - Y + 1, lenx, leny, val) % Mod;
        X = x; Y = y;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
