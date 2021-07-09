/***************************************************************
	File name: P2257.cpp
	Author: ljfcnyali
	Create time: 2019年08月31日 星期六 11时17分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 10000010;

int T, n, m, prime[maxn], tot, miu[maxn], Max = 10000000;
int g[maxn], sum[maxn];
LL ans;
bool vis[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    miu[1] = 1;
    for ( LL i = 2; i <= Max; ++ i )
    {
        if ( !vis[i] ) { prime[++ tot] = i; miu[i] = -1; }
        for ( int j = 1; j <= tot && prime[j] * i <= Max; ++ j )
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) { miu[i * prime[j]] = 0; break ; }
            miu[i * prime[j]] = -miu[i];
        }
    }
    REP(i, 1, tot) for ( int j = 1; j * prime[i] <= Max; ++ j ) g[j * prime[i]] += miu[j];
    REP(i, 1, Max) sum[i] = sum[i - 1] + g[i];
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d", &n, &m); ans = 0;
        int i = 1;
        while ( i <= min(n, m) ) 
        {
            int j = min(n / (n / i), m / (m / i));
            ans += (1LL) * (sum[j] - sum[i - 1]) * (n / i) * (m / i);
            i = j + 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
