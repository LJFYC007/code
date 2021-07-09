/***************************************************************
	File name: sequence.cpp
	Author: ljfcnyali
	Create time: 2020年05月24日 星期日 09时40分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 1e9 + 7;

int n, m, a[maxn], prime[maxn], phi[maxn], tot, f[maxn], ans;
bool vis[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void read(int &x) 
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

namespace Subtask1 
{
    inline void DFS(int x, int sum)
    {
        if ( x == n + 1 ) { ans = (ans + phi[sum + 1]) % Mod; return ; }
        DFS(x + 1, sum);
        if ( (a[x] & sum) == 0 ) DFS(x + 1, sum | a[x]);
    }

    inline int main()
    {
        REP(i, 1, n) scanf("%lld", &a[i]);
        DFS(1, 0);
        printf("%lld\n", (ans + Mod) % Mod);
        return 0;
    }
}

namespace Subtask2
{
    inline int main()
    {
        int Max = 0;
        REP(i, 1, n) { int x; read(x); Max = max(Max, x); ++ a[x]; }
        f[0] = m = 1;
        while ( m <= Max ) m <<= 1;
        -- m;
        REP(i, 0, m) 
        {
            int t = m ^ i;
            for ( int j = t; j > i; j = (j - 1) & t )
                f[i | j] = (f[i | j] + f[i] * a[j]) % Mod;
        }
        REP(i, 0, m) ans = (ans + phi[i + 1] * f[i]) % Mod;
        ans = ans * power(2, a[0]) % Mod;
        printf("%lld\n", (ans + Mod) % Mod);
        return 0;
    }
}

signed main()
{
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    n = maxn - 10; phi[1] = 1;
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
    return Subtask2 :: main();
    if ( n <= 20 ) return Subtask1 :: main();
    return Subtask2 :: main();
}
