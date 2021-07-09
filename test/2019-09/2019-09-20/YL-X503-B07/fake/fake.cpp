/***************************************************************
	File name: fake.cpp
	Author: ljfcnyali
	Create time: 2019年09月20日 星期五 20时39分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 100010;
const int Mod = 998244353;

int T, n, m, k, a[maxn], ans;

inline int power(int a, int b)
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = (r * a) % Mod; b >>= 1; a = (a * a) % Mod; }
    return r;
}

namespace Subtask1
{
    bool vis[maxn];

    inline void DFS(int x)
    {
        if ( x == m + 1 ) 
        {
            if ( a[1] >= k ) ans = (ans + 1) % Mod;
            return ;
        }
        REP(i, 1, n) 
        {   
            if ( vis[i] ) continue ;
            vis[i] = true; int tmp = a[i]; a[i] = 0;
            if ( i > 1 ) a[i - 1] += tmp; else a[n] += tmp;
            if ( i < n ) a[i + 1] += tmp; else a[1] += tmp;
            DFS(x + 1);
            vis[i] = false; a[i] = tmp;
            if ( i > 1 ) a[i - 1] -= tmp; else a[n] -= tmp;
            if ( i < n ) a[i + 1] -= tmp; else a[1] -= tmp;
        }
    }

    inline void Solve()
    {
        mem(vis); DFS(1);
        int sum = 1; REP(i, n - m + 1, n) sum = (sum * i) % Mod;
        printf("%lld\n", (ans * power(sum, Mod - 2)) % Mod);
    }
}

namespace Subtask2
{
    inline void Solve()
    {
        int sum = n; ans = 0;
        REP(i, 1, n)
        {
            int tmp = a[i]; a[i] = 0;
            if ( i > 1 ) a[i - 1] += tmp; else a[n] += tmp;
            if ( i < n ) a[i + 1] += tmp; else a[1] += tmp;
            if ( a[1] >= k ) ++ ans;
            a[i] = tmp;
            if ( i > 1 ) a[i - 1] -= tmp; else a[n] -= tmp;
            if ( i < n ) a[i + 1] -= tmp; else a[1] -= tmp;
        }
        printf("%lld\n", (ans * power(sum, Mod - 2)) % Mod);
    }
}

signed main()
{
    freopen("fake.in", "r", stdin);
    freopen("fake.out", "w", stdout);
    scanf("%lld", &T);
    while ( T -- ) 
    {
        ans = 0;
        scanf("%lld%lld%lld", &n, &m, &k);
        REP(i, 1, n) scanf("%lld", &a[i]);
        if ( n <= 9 ) { Subtask1 :: Solve(); continue ; }
        if ( m == 1 ) { Subtask2 :: Solve(); continue ; }
        puts("0");
    }
    return 0;
}
