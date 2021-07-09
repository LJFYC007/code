/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年07月23日 星期四 08时59分03秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 5e5 + 10;
const int Mod = 1e9 + 7;

int n, k, q, f[maxn], fac[maxn], inv[maxn], val, G[maxn];
pii g[maxn];

pii operator + (pii a, pii b) { return pii((a.x + b.x) % Mod, (a.y + b.y) % Mod); }
pii operator - (pii a, pii b) { return pii((a.x - b.x) % Mod, (a.y - b.y) % Mod); }
pii operator * (pii a, int b) { return pii(a.x * b % Mod, a.y * b % Mod); }

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

inline int sgn(int x) { return x & 1 ? -1 : 1; }

inline int F(pii x, int y) { return (x.x + x.y * y) % Mod; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    n = maxn - 3; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld%lld%lld", &n, &k, &q);
    REP(i, 0, k) scanf("%lld", &f[i]);
    g[0] = pii(0, 1);
    REP(i, 1, k + 1)
    {
        g[i] = g[i - 1] + pii(f[i - 1], 0);
        g[i] = g[i] * power(q, Mod - 2);
    }
    pii x;
    REP(i, 0, k + 1) x = x + g[i] * C(k + 1, i) * sgn(k + 1 - i);
    int val = -x.x * power(x.y, Mod - 2) % Mod;
    REP(i, 0, k) G[i] = F(g[i], val);
    
    if ( k <= 3000 ) 
    { 
    int ans = 0;
    REP(i, 0, k)
    {
        int ret = 1;
        REP(j, 0, k) if ( j != i ) ret = (ret * (n + 1 - j) % Mod) * power(i - j, Mod - 2) % Mod;
        ans = (ans + ret * G[i]) % Mod;
    }
    ans = (power(q, n + 1) * ans - G[0]) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
    }
    
    int ans = 0, sum = 1;
    REP(i, 0, k) sum = sum * ((n + 1 - i) % Mod) % Mod;
    REP(i, 0, k)
    {
        int ret = inv[i] * inv[k - i] * sgn(k - i) % Mod;
        ret = ret * sum % Mod;
        ret = ret * power((n + 1 - i) % Mod, Mod - 2) % Mod;
        ans = (ans + ret * G[i]) % Mod;
    }
    ans = (power(q, n + 1) * ans - G[0]) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
