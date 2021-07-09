/***************************************************************
    File name: B.cpp
    Author: ljfcnyali
    Create time: 2020年07月24日 星期五 09时02分17秒
***************************************************************/
#include<bits/stdc++.h>
  
using namespace std;
  
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int unsigned int
typedef unsigned long long LL;
#define pii pair<int, LL>
  
const int maxn = 1e6 + 4e5 + 10;
const int N = maxn - 10;
const int w = (1 << 30) - 1;
  
int k, ans, miu[maxn], g[maxn], prime[maxn], tot, F[maxn], phi[maxn];
vector<pii> G;
LL n;
bool vis[maxn];
map<int, int> Map1, Map2, Map3, Map4;
  
inline LL power(LL a, int b) { LL r = 1; while ( b ) { if ( b & 1 ) r *= a; a *= a; b >>= 1; } return r; }
  
inline int Solve1(LL n)
{
    if ( n <= N ) return miu[n];
    if ( Map1.count(n) ) return Map1[n];
    int ret = 1;
    for ( LL i = 2, j; i <= n; i = j + 1 ) 
    {
        j = n / (n / i);
        ret -= Solve1(n / i) * (j - i + 1);
    }
    Map1[n] = ret; return ret;
}
  
inline int Solve2(LL n)
{
    if ( n <= N ) return g[n];
    if ( Map2.count(n) ) return Map2[n];
    int ret = sqrt(n);
    for ( LL i = 2, j; i <= n; i = j + 1 ) 
    {
        j = n / (n / i);
        ret -= Solve2(n / i) * (j - i + 1);
    }
    Map2[n] = ret; return ret;
}
  
inline int sgn(int x) { return x & 1 ? -1 : 1; }
 
inline int Solve4(const int n)
{
    int ret = miu[n]; 
    REP(d, 2, k) for ( auto i : G[d] ) 
    {
        const LL tmp = i.second;
        if ( tmp > n ) break ;
        ret += i.first * g[n / tmp];
    }
    return ret;
}
  
inline int Solve(const LL n)
{
    if ( n <= N ) return F[n];
    if ( Map4.count(n) ) return Map4[n]; int ret = Solve1(n); 
    REP(d, 2, k) for ( auto i : G[d] ) 
    {
        const LL tmp = i.second;
        if ( tmp > n ) break ;
        ret += i.first * Solve2(n / tmp);
    }
    Map4[n] = ret; return ret;
}
  
inline int Solve3(LL n)
{
    if ( n <= N ) return phi[n];
    if ( Map3.count(n) ) return Map3[n];
    LL ret = n * (n + 1) / 2;
    for ( LL i = 2, j; i <= n; i = j + 1 ) 
    {
        j = n / (n / i);
        ret -= Solve3(n / i) * (j - i + 1);
    }
    Map3[n] = ret; return ret;
}
  
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    n = N; miu[1] = g[1] = phi[1] = 1;
    REP(i, 2, n)
    {
        if ( !vis[i] ) { prime[++ tot] = i; miu[i] = g[i] = -1; phi[i] = i - 1; }  
        for ( int j = 1; j <= tot && i * prime[j] <= n; ++ j ) 
        {
            vis[i * prime[j]] = true; 
            if ( i % prime[j] == 0 ) 
            { 
                miu[i * prime[j]] = 0; g[i * prime[j]] = -g[i]; 
                phi[i * prime[j]] = phi[i] * prime[j];
                break ; 
            }
            miu[i * prime[j]] = -miu[i]; g[i * prime[j]] = -g[i];
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
    scanf("%llu%u", &n, &k);
    for ( int i = 1; power(i, 3) <= n; ++ i ) 
    {

    }
    REP(d, 2, k) for ( int i = 1; power(i, d + 1) <= n; ++ i ) 
    {
        int x = (g[i] <= 1 ? g[i] : sgn(d + 1)) * miu[i];
        if ( x ) G[d].push_back(pii(x, power(i, d + 1)));
    }
    REP(i, 1, N) { miu[i] += miu[i - 1]; g[i] += g[i - 1]; phi[i] += phi[i - 1]; }
    REP(i, 1, N) F[i] = Solve4(i); 
    for ( LL i = 1, j; i <= n; i = j + 1 ) 
    {
        j = n / (n / i);
        ans += (Solve(j) - Solve(i - 1)) * (2 * Solve3(n / i) - 1);
    }
    printf("%u\n", ans & w);
    return 0;
}
