/***************************************************************
	File name: P4213.cpp
	Author: ljfcnyali
	Create time: 2019年09月01日 星期日 08时42分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int LL
typedef long long LL;

const int maxn = 2000010;

int T, n, Sum[maxn], miu[maxn], prime[maxn], tot, Max = 2000000;
map<int, int> sum;
bool vis[maxn];

inline int GetMiu(int x)
{
    if ( x <= Max ) return Sum[x];
    if ( sum[x] ) return sum[x];
    int ans = 1ll, i = 2;
    while ( i <= x ) 
    {
        int j = x / (x / i);
        ans -= (j - i + 1) * GetMiu(x / i);
        i = j + 1;
    }
    sum[x] = ans;
    return ans;
}

inline int GetPhi(int x)
{
    int i = 1, ans = 0ll;
    while ( i <= x ) 
    {
        int j = x / (x / i);
        ans += (GetMiu(j) - GetMiu(i - 1)) * (x / i) * (x / i);
        i = j + 1;
    }
    return (ans - 1) / 2 + 1;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    miu[1] = 1;
    REP(i, 2, Max)
    {
        if ( !vis[i] ) { prime[++ tot] = i; miu[i] = -1; }
        for ( int j = 1; j <= tot && i * prime[j] <= Max; ++ j )
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) { miu[i * prime[j]] = 0; break ; }
            miu[i * prime[j]] = -miu[i];
        }
    }
    REP(i, 1, Max) Sum[i] = Sum[i - 1] + miu[i];
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld", &n);
        printf("%lld %lld\n", GetPhi(n), GetMiu(n));
    }
    return 0;
}
