/***************************************************************
	File name: P2522.cpp
	Author: ljfcnyali
	Create time: 2019年08月28日 星期三 21时13分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 500010;

int miu[maxn], prime[maxn], tot, sum[maxn], a, b, c, d, k, ans;
bool vis[maxn];

inline int Solve(int n, int m)
{
    int i = 1, num = 0;
    while ( i <= min(n, m) ) 
    {
        int j = min(n / (n / i), m / (m / i));
        num += (sum[j] - sum[i - 1]) * (n / i) * (m / i);
        i = j + 1;
    }
    return num;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T; scanf("%d", &T);
    miu[1] = sum[1] = 1;
    REP(i, 2, 50000) 
    {
        if ( !vis[i] ) { prime[++ tot] = i; miu[i] = -1; }
        for ( int j = 1; j <= tot && prime[j] * i <= 50000; ++ j )
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) break ;
            miu[i * prime[j]] = -miu[i];
        }
        sum[i] = sum[i - 1] + miu[i];
    }
    while ( T -- ) 
    {
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
        -- a; -- c; a /= k; b /= k; c /= k; d /= k;
        ans = Solve(b, d);
        ans -= Solve(a, d) + Solve(b, c);
        ans += Solve(a, c);
        printf("%d\n", ans);
    }
    return 0;
}
