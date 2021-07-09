/***************************************************************
	File name: P1829.cpp
	Author: ljfcnyali
	Create time: 2019年09月01日 星期日 15时58分15秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 10000010;

int Max = 10000000, n, m, ans, Mod = 20101009;
int prime[maxn], tot, f[maxn], sum[maxn];
bool vis[maxn];

inline int calc(int x) { x %= Mod; return (x * (x + 1) / 2) % Mod; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    f[1] = 1;
    REP(i, 2, Max)
    {
        if ( !vis[i] ) { prime[++ tot] = i; f[i] = (1 - i) % Mod; }
        for ( int j = 1; j <= tot && prime[j] * i <= Max; ++ j )
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) { f[i * prime[j]] = f[i]; break ; }
            f[i * prime[j]] = (f[i] * f[prime[j]]) % Mod;
        }
    }
    REP(i, 1, Max) sum[i] = (sum[i - 1] + i * f[i]) % Mod;
    int i = 1;
    while ( i <= min(n, m) ) 
    {
        int j = min(n / (n / i), m / (m / i));
        int Sum = (sum[j] - sum[i - 1]) % Mod; Sum = (Sum + Mod) % Mod;
        ans = (ans + ((Sum * ((calc(n / i) * calc(m / i)) % Mod)) % Mod)) % Mod;
        i = j + 1;
    }
    printf("%lld\n", ans);
    return 0;
}
