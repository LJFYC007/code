/***************************************************************
	File name: P2568.cpp
	Author: ljfcnyali
	Create time: 2019年08月29日 星期四 20时11分35秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 10000010;

int n, ans, prime[maxn], tot, phi[maxn];
bool vis[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    phi[1] = 1;
    REP(i, 2, n) 
    {
        if ( !vis[i] ) { prime[++ tot] = i; phi[i] = i - 1; }
        for ( int j = 1; j <= tot && prime[j] * i <= n; ++ j ) 
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) 
            {
                phi[i * prime[j]] = phi[i] * prime[j];
                break ; 
            }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
    REP(i, 2, n) phi[i] += phi[i - 1];
    REP(i, 1, tot) ans += phi[n / prime[i]] * 2 - 1;
    printf("%lld\n", ans);
    return 0;
}
