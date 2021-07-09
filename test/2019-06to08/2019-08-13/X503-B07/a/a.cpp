/***************************************************************
	File name: a.cpp
	Author: ljfcnyali
	Create time: 2019年08月13日 星期二 08时17分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1000010;
const LL Mod = 1e9 + 7;

LL prime[maxn], v[maxn], sum;

inline void Get_Prime()
{
    REP(i, 2, 1000000)
    {
        if ( !v[i] ) { v[i] = i; prime[++ sum] = i; }
        REP(j, 1, sum)
        {
            if ( prime[j] * i > 1000000 ) break ;
            v[prime[j] * i] = prime[j];
        }
    }
}

namespace Subtask1
{

    inline void Solve()
    {
        LL ans = 1, n;
        scanf("%lld", &n);
        Get_Prime();
        REP(i, 1, sum)
        {
            if ( prime[i] * prime[i] > n ) break ;
            LL s = 0; while ( n % prime[i] == 0 ) { n /= prime[i]; ++ s; }
            ans = (ans * (1 + 2 * s)) % Mod;
        }
        if ( n > 1 ) ans *= 3;
        printf("%lld\n", ans);
    }
}

namespace Subtask2
{
    int sum[maxn];

    inline void Solve(int x)
    {
        for ( int i = 2; i * i <= x; ++ i ) 
            while ( x % i == 0 ) { ++ sum[i]; x /= i; }
        if ( x > 1 ) ++ sum[x];
    }

    inline void Solve()
    {
        LL ans = 1, n; scanf("%lld", &n);
        REP(i, 2, n) Solve(i);
        REP(i, 2, n) ans = (ans * (1 + 2 * sum[i])) % Mod;
        printf("%lld\n", ans);
    }
}

int main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    int T; scanf("%d", &T);
    if ( T == 1 ) Subtask1 :: Solve();
    else if ( T == 2 ) Subtask2 :: Solve();
    return 0;
}
