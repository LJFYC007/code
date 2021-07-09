/***************************************************************
	File name: island.cpp
	Author: ljfcnyali
	Create time: 2020年06月06日 星期六 07时59分46秒
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
const int INF = 1e18;

int n, l[maxn], r[maxn], h[maxn], ans, fac[maxn], inv[maxn];
char s[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int A(int n, int m) { return n < m ? 0 : fac[n] * inv[n - m] % Mod; }

inline int Get(int l, int r) { return l <= r ? ((r - l + 1) * (l + r) / 2) % Mod : 0; }

inline void Solve(int l, int r, int dep)
{
    if ( l > r ) return ;
    int Min = INF, pos = 0;
    REP(i, l, r) if ( h[i] < Min ) { Min = h[i]; pos = i; }

    int X = r - l + 1, Y = Min - dep, ret = 0, sum1 = 0, sum2 = 0, num1 = 0, num2 = 0;
    if ( X == 1 || Y == 1 ) 
    {
        REP(i, 1, X) ret = (ret + Get(1, X - i)) % Mod;
        REP(i, 1, Y) ret = (ret + Get(1, Y - i)) % Mod;
    }
    else 
    {   
        REP(i, 1, X) sum1 = (sum1 + Get(1, X - i)) % Mod;
        REP(i, 1, Y) sum2 = (sum2 + Get(1, Y - i)) % Mod;
        ret = (sum1 * Y * Y + sum2 * X * X) % Mod;
    }

    sum1 = sum2 = num1 = num2 = 0;
    REP(i, l, pos - 1) { sum1 = (sum1 + Get(1, h[i] - Min - 1)) % Mod; num1 = (num1 + h[i] - Min) % Mod; }
    REP(i, pos + 1, r) { sum2 = (sum2 + Get(1, h[i] - Min)) % Mod; num2 = (num2 + h[i] - Min) % Mod; }
    ret = (ret + sum1 * num2 + sum2 * num1) % Mod;
    ret = (ret + num1 * num2) % Mod;
    sum1 = sum2 = 0;
    REP(i, l, pos - 1) { sum1 = (sum1 + h[i] - Min) % Mod; sum2 = (sum2 + sum1) % Mod; }
    ret = (ret + sum2 * num2) % Mod;
    sum1 = sum2 = 0;
    for ( int i = r; i > pos; -- i ) { sum1 = (sum1 + h[i] - Min) % Mod; sum2 = (sum2 + sum1) % Mod; }
    ret = (ret + sum2 * num1) % Mod;

    int num = X * Y % Mod;
    REP(i, l, r)
    {
        ret = (ret + Get(1, h[i] - Min) * num) % Mod;
        sum1 = (Get(1, r - i) + Get(1, i - l)) * Y % Mod; 
        sum2 = Get(1, Y - 1) * X % Mod;
        ret = (ret + (sum1 + sum2) * (h[i] - Min)) % Mod;
    }
    ans = (ans + ret) % Mod;

    Solve(l, pos - 1, Min);
    Solve(pos + 1, r, Min);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("island.in", "r", stdin);
    freopen("island.out", "w", stdout);
#endif
    n = maxn - 10;
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;

    scanf("%lld%s", &n, s);
    REP(i, 1, n) scanf("%lld%lld", &l[i], &r[i]); 

    int sum1 = 0, sum2 = 0, num1 = 0, num2 = 0, sum = 0, num = 0;
    for ( int i = n; i >= 1; -- i ) 
    {
        sum = (sum + Get(1, r[i] - 1)) % Mod;
        num = (num + r[i]) % Mod;
        num2 = (num2 + r[i]) % Mod; 
        sum2 = (sum2 + num2) % Mod;
    }
    REP(i, 1, n)
    {
        sum2 = (sum2 - num2) % Mod; 
        num2 = (num2 - r[i]) % Mod;
        int ret = (sum1 + sum2 + sum) % Mod;
        ans = (ans + ret * (-l[i]) + num * Get(1, -l[i])) % Mod;
        num1 = (num1 + r[i]) % Mod;
        sum1 = (sum1 + num1) % Mod; 
    }

    REP(i, 1, n) h[i] = -l[i];
    Solve(1, n, 0);
    REP(i, 1, n) h[i] = r[i];
    Solve(1, n, 0);
    ans = ans * 2 % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
