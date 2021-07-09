/***************************************************************
	File name: a.cpp
	Author: ljfcnyali
	Create time: 2019年10月16日 星期三 09时25分41秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5010;
const int Mod = 1e9 + 7;

int n, m, p[300010], inv[300010], ans, g[maxn];
struct node 
{ 
    int x, y, z; 
    bool operator < (const node &a) const { return x + y + z < a.x + a.y + a.z; }
} a[maxn];

inline int f(int a, int b, int c) 
{ 
    return (p[a + b + c] * (inv[a] * inv[b] % Mod) % Mod) * inv[c] % Mod; 
}

inline int power(int a, int b) 
{ 
    int r = 1; 
    while ( b ) 
    { 
        if ( b & 1 ) r = r * a % Mod; 
        a = a * a % Mod; 
        b >>= 1; 
    } 
    return r; 
}

inline int Solve(int x)
{
    g[x] = f(a[x].x, a[x].y, a[x].z);
    REP(i, 1, x - 1)
        if ( a[i].x <= a[x].x && a[i].y <= a[x].y && a[i].z <= a[x].z ) 
            g[x] = (g[x] - g[i] * f(a[x].x - a[i].x, a[x].y - a[i].y, a[x].z - a[i].z)) % Mod;
    return g[x] * f(n - a[x].x, n - a[x].y, n - a[x].z) % Mod;
}

signed main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, m) scanf("%lld%lld%lld", &a[i].x, &a[i].y, &a[i].z);
    sort(a + 1, a + m + 1);
    p[0] = 1; REP(i, 1, 3 * n) p[i] = p[i - 1] * i % Mod;
    REP(i, 0, 3 * n) inv[i] = power(p[i], Mod - 2);
    REP(i, 1, m) ans = (ans + Solve(i)) % Mod; 
    ans = (f(n, n, n) - ans) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
