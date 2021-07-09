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
typedef long long LL;

const int maxn = 1e7 + 10;
const int Mod = 19260817;

int T, n, ans, f[maxn], g[maxn], h[maxn], phi[maxn], prime[maxn], tot;
bool vis[maxn];

inline int power(LL a, int b) 
{ 
    LL r = 1; 
    while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } 
    return r;
}

inline void read(int &x) 
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
    freopen("square.in", "r", stdin);
    freopen("square.out", "w", stdout);
    n = maxn - 10; phi[1] = 1;
    for ( int i = 2; i <= n; ++ i ) 
    {
        if ( !vis[i] ) { prime[++ tot] = i; phi[i] = i - 1; }
        for ( int j = 1; j <= tot && i * prime[j] <= n; ++ j )
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) { phi[i * prime[j]] = phi[i] * prime[j]; break ; }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }

    f[0] = g[0] = 1;
    REP(i, 1, n) { f[i] = (LL)f[i - 1] * i % Mod; g[i] = 1; }
    REP(i, 1, tot)
    {
        const int num = (LL)prime[i] * prime[i] % Mod;
        int x = prime[i], ret;
        while ( x <= n ) 
        {
            ret = prime[i];
            for ( register int j = x; j <= n; j += x ) 
            {
                g[j] = (LL)g[j] * ret % Mod;
                ret = (LL)ret * num % Mod;
            }
            if ( (LL)x * prime[i] > n ) break ;
            x *= prime[i];
        }
    }
    REP(i, 1, n) 
    {
        g[i] = (LL)g[i] * g[i] % Mod;
        g[i] = (LL)g[i] * g[i - 1] % Mod;
    }

    scanf("%d", &T);
    while ( T -- ) 
    {
        read(n); ans = (LL)power(f[n], n + n) * power(g[n], Mod - 2) % Mod;
        printf("%d\n", (ans + Mod) % Mod);
    }
    return 0;
}
