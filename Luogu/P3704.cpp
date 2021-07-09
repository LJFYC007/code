/***************************************************************
	File name: P3704.cpp
	Author: ljfcnyali
	Create time: 2019年09月27日 星期五 15时22分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 1000010;
const int Mod = 1e9 + 7;

int f[maxn], miu[maxn], n, m, T, prime[maxn], tot, p[maxn], g[maxn];
bool vis[maxn];

inline int power(int a, int b)
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = (r * a) % Mod; a = (a * a) % Mod; b >>= 1; }
    return r;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    p[0] = p[1] = miu[1] = f[1] = g[1] = 1;
    REP(i, 2, maxn - 1)
    {
        p[i] = 1;
        f[i] = (f[i - 1] + f[i - 2]) % Mod;
        g[i] = power(f[i], Mod - 2);
        if ( !vis[i] ) { prime[++ tot] = i; miu[i] = -1; }
        for ( int j = 1; j <= tot && i * prime[j] < maxn; ++ j )
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) { miu[i * prime[j]] = 0; break ; }
            miu[i * prime[j]] = -miu[i];
        }
    }
    REP(i, 1, maxn - 1) 
    {
        if ( !miu[i] ) continue ;
        for ( int j = i; j < maxn; j += i ) 
            p[j] = (p[j] * (miu[i] == 1 ? f[j / i] : g[j / i])) % Mod;
    }
    REP(i, 1, maxn - 1) p[i] = (p[i] * p[i - 1]) % Mod;
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld", &n, &m);
        if ( n > m ) swap(n, m);
        int i = 1, ans = 1;
        while ( i <= n )
        {
            int j = min(n / (n / i), m / (m / i));
            int sum = (p[j] * power(p[i - 1], Mod - 2)) % Mod;
            sum = power(sum, ((n / i) * (m / i)) % (Mod - 1));
            ans = (ans * sum) % Mod;
            i = j + 1;
        }
        printf("%lld\n", (ans + Mod) % Mod);
    }
    return 0;
}
