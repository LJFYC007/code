/***************************************************************
	File name: PE530.cpp
	Author: ljfcnyali
	Create time: 2020年06月15日 星期一 21时05分03秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 4e7 + 10;

int n, prime[maxn], tot, phi[maxn];
bool vis[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    phi[1] = 1; n = maxn - 10;
    REP(i, 2, n)
    {
        if ( !vis[i] ) { prime[++ tot] = i; phi[i] = i - 1; }
        for ( int j = 1; j <= tot && i * prime[j] <= n; ++ j ) 
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) { phi[i * prime[j]] = phi[i] * prime[j]; break ; }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
    scanf("%lld", &n);
    int ans = 0;
    for ( int o = 1; o * o <= n; ++ o ) 
    {
        int sum = 0, m = n / o / o;
        for ( int i = 1, j = 0; i <= m; i = j + 1 ) 
        {
            j = m / (m / i);
            sum += (j - i + 1) * (m / i);
        }
        ans += sum * phi[o];
    }
    printf("%lld\n", ans);
    return 0;
}
