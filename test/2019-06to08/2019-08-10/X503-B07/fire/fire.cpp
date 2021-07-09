/***************************************************************
	File name: fire.cpp
	Author: ljfcnyali
	Create time: 2019年08月10日 星期六 09时44分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 300010;
const LL Mod = 1048576;

LL n, q, pos, T, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], ans;
LL sum[maxn], anc[maxn][20], Max[maxn][20], H[maxn];

inline void read(LL &x) 
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

inline void add(LL u, LL v, LL w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

namespace Subtask1
{
    inline void DFS1(LL u, LL k)
    {
        for ( LL i = Begin[u]; i; i = Next[i] ) 
        {
            LL v = To[i];
            if ( W[i] <= k ) { ans += W[i]; DFS1(v, k); }
        }
    }

    inline void Solve()
    {
        while ( q -- )
        {
            LL u, k; read(u); read(k);
            ans = 0;
            DFS1(u, k);
            printf("%lld\n", ans);
        }
    }
}

namespace Subtask2
{
    inline void Solve()
    {
        REP(i, 1, n - 1) { LL x; read(x); read(W[i]); }
        sort(W + 1, W + n);
        REP(i, 1, n - 1) sum[i] = sum[i - 1] + W[i];
        sum[n] = sum[n - 1];
        scanf("%lld", &q);
        while ( q -- )
        {
            LL u, k; read(u); read(k);
            u = u ^ (ans % Mod); k = k ^ (ans % Mod);
            if ( u != 1 ) { ans = 0; printf("%lld\n", ans); continue ; }
            LL x = lower_bound(W + 1, W + n, k) - W;
            ans = sum[x]; 
            printf("%lld\n", ans);
        }
    }
}

namespace Subtask3
{
    inline void DFS1(LL u)
    {
        for ( LL i = Begin[u]; i; i = Next[i] ) 
        {
            LL v = To[i]; 
            anc[u][0] = v; Max[u][0] = W[i];
            H[v] = H[u] + W[i];
            DFS1(v);
        }
    }

    inline void Solve()
    {
        DFS1(1);
        REP(j, 1, 19) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
        REP(j, 1, 19) REP(i, 1, n) Max[i][j] = max(Max[i][j - 1], Max[anc[i][j - 1]][j - 1]); 
        while ( q -- ) 
        {
            LL u, k; read(u); read(k);
            u = u ^ (ans % Mod); k = k ^ (ans % Mod);
            LL x = u;
            for ( LL j = 19; j >= 0; -- j ) if ( anc[u][j] && Max[u][j] <= k ) u = anc[u][j];
            if ( anc[u][0] && Max[u][0] <= k ) u = anc[u][0];
            ans = H[u] - H[x];
            printf("%lld\n", ans);
        }
    }
}

int main()
{
    freopen("fire.in", "r", stdin);
    freopen("fire.out", "w", stdout);
    scanf("%lld%lld%lld", &pos, &n, &T);
    if ( pos == 8 ) { Subtask2 :: Solve(); return 0; }
    REP(i, 1, n - 1) { LL f, w; read(f); read(w); add(f, i + 1, w); }
    scanf("%lld", &q);
    if ( pos <= 3 ) Subtask1 :: Solve();
    else Subtask3 :: Solve();
    return 0;
}
