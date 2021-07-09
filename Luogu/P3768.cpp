/***************************************************************
	File name: P3768.cpp
	Author: ljfcnyali
	Create time: 2019年09月01日 星期日 14时57分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 10000010;

int n, Mod, prime[maxn], tot, phi[maxn], sum[maxn];
int Max = 10000000, Last, Next, inv;
bool vis[maxn];
map<int, int> S;

inline int GetF(int x) 
{
    x %= Mod;
    int ans = x * (x + 1) / 2; ans %= Mod;
    return (ans * ans) % Mod;
}

inline int power(int a, int b)
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = (r * a) % Mod; b >>= 1; a = (a * a) % Mod; }
    return r;
}

inline int calc(int x)
{
    x %= Mod;
    return (((((x * (x + 1)) % Mod) * (2 * x + 1)) % Mod) * inv) % Mod;
}

inline int GetS(int x)
{
    if ( x <= Max ) return sum[x];
    if ( S[x] ) return S[x];
    int i = 2, ans = GetF(x);
    while ( i <= x ) 
    {
        int j = x / (x / i);
        int sum = ((calc(j) - calc(i - 1)) * GetS(x / i)) % Mod;
        ans = (((ans - sum) % Mod) + Mod) % Mod;
        i = j + 1;
    }
    S[x] = ans; return ans;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &Mod, &n);
    inv = power(6, Mod - 2); phi[1] = 1;
    REP(i, 2, Max)
    {
        if ( !vis[i] ) { phi[i] = i - 1; prime[++ tot] = i; }
        for ( int j = 1; j <= tot && i * prime[j] <= Max; ++ j )
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) { phi[i * prime[j]] = phi[i] * prime[j]; break ; }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
    REP(i, 1, Max) sum[i] = ((((i * i % Mod) * phi[i]) % Mod) + sum[i - 1]) % Mod;
    int i = 1, ans = 0;
    while ( i <= n ) 
    {
        int j = n / (n / i); Next = GetS(j);
        int sum = ((Next - Last) * GetF(n / i)) % Mod; 
        sum = (sum + Mod) % Mod; ans = (ans + sum) % Mod;
        Last = Next; i = j + 1;
    }
    printf("%lld\n", ans);
    return 0;
}
