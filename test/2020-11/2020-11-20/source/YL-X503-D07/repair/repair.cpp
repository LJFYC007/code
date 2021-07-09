/***************************************************************
	File name: repair.cpp
	Author: ljfcnyali
	Create time: 2020年11月20日 星期五 14时38分44秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1010;
const int Mod = 1e9 + 7;

int n, m, K, a[maxn], f[1 << 18][40], b[maxn], g[1 << 18][40];
map<int, int> Map;

signed main()
{
    freopen("repair.in", "r", stdin);
    freopen("repair.out", "w", stdout);
    scanf("%lld%lld", &n, &K); 
    REP(i, 1, n) { scanf("%lld", &a[i]); Map[a[i]] = Map[a[i] + 1] = true; }
    for ( auto it : Map ) { ++ m; b[m] = it.first; Map[it.first] = m; }
    REP(i, 1, n) g[1 << i - 1][Map[a[i]]] = 1;
    REP(i, 0, (1 << n) - 1) REP(j, 0, m)
    {
        if ( !g[i][j] ) continue ;
        int t = 0;
        REP(k, 1, n) if ( (i >> k - 1) & 1 ) t = t * 2 + 1;
        t /= 2;
        REP(k, 1, n)
        {
            if ( (i >> k - 1) & 1 ) continue ;
            int x = b[j], y = a[k], z = (x == y ? x + 1 : max(x, y)), w = Map[z];
            g[i | (1 << k - 1)][w] = (g[i | (1 << k - 1)][w] + g[i][j]) % Mod;
            f[i | (1 << k - 1)][w] = (f[i | (1 << k - 1)][w] + g[i][j] * (K * z % Mod + t) + f[i][j]) % Mod;
        }
    }
    for ( int i = m; i >= 0; -- i ) 
        if ( g[(1 << n) - 1][i] ) 
        {
            printf("%lld %lld\n", b[i], (f[(1 << n) - 1][i] + Mod) % Mod);
            return 0;
        }
    return 0;
}
