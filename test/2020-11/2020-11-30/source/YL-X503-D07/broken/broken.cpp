/***************************************************************
	File name: broken.cpp
	Author: ljfcnyali
	Create time: 2020年11月30日 星期一 10时52分43秒
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

int n, m, k, fac[maxn], inv[maxn];
struct node { int x, y, z; } a[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

inline int sgn(int x) { return x & 1 ? -1 : 1; }

inline int Solve(int n, int m, int x)
{
    if ( n < 0 || m < 0 ) return 0;
    int ret = 0;
    REP(i, 0, m) ret = (ret + C(m, i) * sgn(m - i) * power(i + x, n)) % Mod;
    ret = ret * inv[m] % Mod;
    return ret;
}

signed main()
{
    freopen("broken.in", "r", stdin);
    freopen("broken.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &k);
    fac[0] = inv[0] = 1; REP(i, 1, m) fac[i] = fac[i - 1] * i % Mod;
    inv[m] = power(fac[m], Mod - 2); for ( int i = m - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    REP(i, 1, k) { scanf("%lld%lld%lld", &a[i].x, &a[i].y, &a[i].z); a[i].z -= Solve(a[i].x, a[i].y, 0); }
    int ans = Solve(n, m, 0);
    REP(i, 1, k)
    {
        ans = (ans + Solve(n - a[i].x, m - a[i].y, a[i].y) * a[i].z) % Mod; 
        REP(j, i + 1, k) a[j].z = (a[j].z - Solve(a[j].x - a[i].x, a[j].y - a[i].y, a[i].y) * a[i].z) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
