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

const int maxn = 1e7 + 10;
const int Mod = 998244353;

int n, m, a[maxn], f[maxn], g[maxn];

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
    g[0] = n - 1;
    REP(i, 1, m)
    {
        int x = (m * (n - 1) + (i * (n - 1) % Mod) * g[i - 1]) % Mod;
        g[i] = power(m - i, Mod - 2) * x % Mod; 
    }
    f[m] = 0;
    for ( int i = m - 1; i >= 0; -- i ) f[i] = (f[i + 1] + g[i]) % Mod;
    
    int ans = 0;
    REP(i, 1, n) ans = (ans + f[a[i]]) % Mod;
    ans = (ans - f[0] * (n - 1)) % Mod;
    printf("%lld\n", (ans * power(n, Mod - 2) % Mod + Mod) % Mod);
    return 0;
}
