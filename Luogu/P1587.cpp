/***************************************************************
	File name: P1587.cpp
	Author: ljfcnyali
	Create time: 2019年09月01日 星期日 10时24分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int LL
typedef long long LL;

const int maxn = 20000010;

int n, m, k, prime[maxn], tot, miu[maxn], sum[maxn];
int F[maxn], Last, Next, Max = 20000000;
bool vis[maxn];
map<pair<int, int>, int> G;

inline int GetF(int x) { return (x / k) * F[k] + F[x % k]; }

inline int GetG(int x, int k)
{
    if ( (k == 1 && x <= Max) || !x ) return sum[x];
    if ( G[make_pair(x, k)] ) return G[make_pair(x, k)];
    if ( k == 1 ) 
    {
        int i = 2, ans = 1; 
        while ( i <= x ) 
        {
            int j = x / (x / i);
            ans -= (j - i + 1) * GetG(x / i, 1);
            i = j + 1;
        }
        if ( k % 2 == 1 ) G[make_pair(x, k)] = ans; return ans;
    }
    int ans = 0;
    for ( int i = 1; i * i <= k; ++ i )
    {
        if ( k % i != 0 ) continue ;
        if ( miu[i] ) ans += GetG(x / i, i);
        if ( i * i != k && miu[k / i] ) ans += GetG(x / (k / i), k / i);
    }
    G[make_pair(x, k)] = ans; return ans;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &m, &k);
    REP(i, 1, k) F[i] = F[i - 1] + (__gcd(i, k) == 1);
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
    REP(i, 1, Max) sum[i] = sum[i - 1] + miu[i];
    int i = 1, ans = 0;
    while ( i <= min(n, m) ) 
    {
        int j = min(n / (n / i), m / (m / i));
        Next = GetG(j, k);
        ans += (Next - Last) * (n / i) * GetF(m / i);
        Last = Next; i = j + 1;
    }
    printf("%lld\n", ans);
    return 0;
}
