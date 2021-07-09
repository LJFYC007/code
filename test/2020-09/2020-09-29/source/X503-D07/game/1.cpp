/***************************************************************
	File name: game.cpp
	Author: ljfcnyali
	Create time: 2020年09月29日 星期二 08时46分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;
#define x first
#define y second

const int maxn = 1e5 + 10;
const int Mod = 998244353;

int n, m, a[maxn], g[maxn];
pii f[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline pii operator + (pii a, pii b) { return pii((a.x + b.x) % Mod, (a.y + b.y) % Mod); }
inline pii operator - (pii a, pii b) { return pii((a.x - b.x) % Mod, (a.y - b.y) % Mod); }
inline pii operator * (pii a, int b) { return pii(a.x * b % Mod, a.y * b % Mod); }
inline pii operator + (pii a, int b) { return pii(a.x, (a.y + b) % Mod); }
inline pii operator - (pii a, int b) { return pii(a.x, (a.y - b) % Mod); }

signed main()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) { scanf("%lld", &a[i]); m += a[i]; }
    f[0] = pii(0, 0); f[1] = pii(1, 0);
    int invm = power(m, Mod - 2), invn = power(n - 1, Mod - 2);
    REP(i, 1, m - 1)
    {
        int x = (invm * i % Mod) * (invn * (n - 2) % Mod) % Mod;      
        pii t = f[i] * (1 - x) - 1; 
        t = t - f[i - 1] * (invm * (m - i + 1) % Mod);
        f[i + 1] = t * power((invm * (i + 1) % Mod) * invn % Mod, Mod - 2);
    }
    int x = -f[m].y * power(f[m].x, Mod - 2) % Mod;
    REP(i, 0, m) g[i] = (f[i].x * x + f[i].y) % Mod;
    REP(i, 0, m) printf("%lld ", (g[i] + Mod) % Mod); puts("");
    int ans = 0;
    REP(i, 1, n) ans += g[a[i]];
    ans = ans * power(n, Mod - 2) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
