/***************************************************************
	File name: 1.cpp
	Author: ljfcnyali
	Create time: 2019年10月08日 星期二 16时13分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 30000010;
const int Mod = 998244353;

int prime[maxn], tot, phi[maxn], miu[maxn], n;
bool vis[maxn];

inline int Solve(int x)
{
    int i = 1; LL ans = 0;
    while ( i <= x )
    {
        int j = x / (x / i); LL sum = (miu[j] - miu[i - 1] + Mod) % Mod;
        LL tmp = ((x / i) * (x / i + 1) / 2) % Mod; 
        tmp = (tmp * tmp) % Mod;
        ans = (ans + tmp * sum) % Mod;
        i = j + 1;
    }
    return ans;
}

signed main()
{
#ifndef ONLINE_JUDGE
     freopen("math.in", "r", stdin);
     freopen("math.out", "w", stdout);
#endif
    scanf("%d", &n);
    phi[1] = miu[1] = 1;
    REP(i, 2, n)
    {
        if ( !vis[i] ) { prime[++ tot] = i; phi[i] = i - 1; miu[i] = -1; }
        for ( int j = 1; j <= tot && (LL)i * prime[j] <= (LL)n; ++ j ) 
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) { miu[i * prime[j]] = 0; phi[i * prime[j]] = (phi[i] * prime[j]) % Mod; break ; }
            miu[i * prime[j]] = -miu[i];
            phi[i * prime[j]] = (phi[i] * phi[prime[j]]) % Mod;
        }
    }
    REP(i, 1, n) phi[i] = (phi[i - 1] + phi[i] * (i * i % Mod)) % Mod;
    REP(i, 1, n) miu[i] = (miu[i - 1] + miu[i] * (i * i % Mod)) % Mod;
    int i = 1; LL ans = 0;
    while ( i <= n ) 
    {
        int j = n / (n / i); LL sum = (phi[j] - phi[i - 1] + Mod) % Mod;
        ans = (ans + sum * Solve(n / i)) % Mod;
        i = j + 1;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
