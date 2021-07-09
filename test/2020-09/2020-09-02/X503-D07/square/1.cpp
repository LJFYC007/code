/***************************************************************
	File name: square.cpp
	Author: ljfcnyali
	Create time: 2020年09月02日 星期三 19时24分11秒
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
const int Mod = 19260817;

int T, n, ans, f[maxn], g[maxn], h[maxn], miu[maxn], prime[maxn], tot;
bool vis[maxn];

inline int power(int a, int b) 
{ 
    int r = 1; bool flag = false; 
    if ( b < 0 ) { flag = true; b = -b; }
    while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } 
    return flag ? power(r, Mod - 2) : r; 
}

signed main()
{
    freopen("square.in", "r", stdin);
    freopen("square.out", "w", stdout);
    n = maxn - 10;
    miu[1] = 1;
    for ( int i = 2; i <= n; ++ i ) 
    {
        if ( !vis[i] ) { prime[++ tot] = i; miu[i] = -1; }
        for ( int j = 1; j <= tot && i * prime[j] <= n; ++ j )
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) { miu[i * prime[j]] = 0; break ; }
            miu[i * prime[j]] = -miu[i];
        }
    }

    f[1] = 1; REP(i, 2, n) f[i] = f[i - 1] * i % Mod;
    REP(i, 1, n) g[i] = h[i] = 1;
    REP(i, 1, n) for ( int j = i; j <= n; j += i ) 
    {
        h[j] = h[j] * power(i, miu[j / i]) % Mod;
        int x = ((j / i) * (j / i) - ((j / i) - 1) * ((j / i) - 1)) % Mod;
        g[j] = g[j] * power(h[i], x + x) % Mod;
    }
    REP(i, 2, n) g[i] = g[i - 1] * g[i] % Mod;

    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld", &n); 
        ans = power(f[n], n + n) * power(g[n], Mod - 2) % Mod;
        printf("%lld\n", ans);
    }
    return 0;
}
