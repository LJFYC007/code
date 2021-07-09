/***************************************************************
	File name: P3327.cpp
	Author: ljfcnyali
	Create time: 2019年08月29日 星期四 13时12分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 50010;

int n, m, T, miu[maxn], d[maxn], sum1[maxn], sum2[maxn], prime[maxn], num[maxn], tot;
bool vis[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    miu[1] = d[1] = 1;
    REP(i, 2, 50000)
    {
        if ( !vis[i] ) { miu[i] = -1; d[i] = 2; num[i] = 1; prime[++ tot] = i; }
        for ( int j = 1; j <= tot && prime[j] * i <= 50000; ++ j )
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) 
            { 
                miu[i * prime[j]] = 0;
                num[i * prime[j]] = num[i] + 1;
                d[i * prime[j]] = d[i] / num[i * prime[j]] * (num[i * prime[j]] + 1);
                break ; 
            }
            d[i * prime[j]] = d[i] * 2; num[i * prime[j]] = 1;
            miu[i * prime[j]] = -miu[i];
        }
    }
    REP(i, 1, 50000) sum1[i] = sum1[i - 1] + miu[i], sum2[i] = sum2[i - 1] + d[i];
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld", &n, &m);
        int i = 1, ans = 0;
        while ( i <= min(n, m) )
        {
            int j = min(n / (n / i), m / (m / i));
            ans += (sum1[j] - sum1[i - 1]) * sum2[n / i] * sum2[m / i];
            i = j + 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
