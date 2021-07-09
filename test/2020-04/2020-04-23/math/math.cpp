/***************************************************************
	File name: math.cpp
	Author: ljfcnyali
	Create time: 2020年04月23日 星期四 13时43分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;
const int Mod = 1073741824;
const int block = 10000;

int n, m, miu[maxn], prime[maxn], tot, d[maxn], num[maxn], f[maxn], h[30][30][maxn];
vector<int> g[maxn];
bool vis[maxn];

inline int F(int p, int n)
{
    return g[p][n];
    /*
    if ( p <= block ) return g2[p][n];
    else return g1[p][n];
    int ans = 0;
    REP(i, 1, n) ans += d[i] * f[i * p];
    return ans;
*/
    /*
    int ans = 0;
    REP(i, 1, p)
    {
        if ( p % i != 0 ) continue ;
        int ret = 0;
        REP(d1, 1, n / i) REP(t, 1, n / d1 / i) 
        {
            int sum = 0;
            REP(j, 1, p)
            {
                if ( p % j != 0 ) continue ;
                sum += miu[i * j * d1] * d[t * p / j] * d[t * p / j];
            }
            ret += sum * d[i * t * d1];
        }
        ans += ret * miu[i];
    }
    */
    /*
    REP(i, 1, n)
    {
        int sum = 0;
        REP(d1, 1, p) REP(d2, 1, i)
        {
            if ( p % d1 != 0 || i % d2 != 0 ) continue ;
            if ( __gcd(i, d1) == 1 ) sum += miu[d1 * d2] * d[i * p / d1 / d2] * d[i * p / d1 / d2];
        }
        ans += sum * d[i];
    }
    */
   // return ans;
}

int main()
{
    freopen("math.in", "r", stdin);
    freopen("math.out", "w", stdout);
    n = maxn - 10;
    miu[1] = d[1] = 1;
    REP(i, 2, n)
    {
        if ( !vis[i] ) { prime[++ tot] = i; miu[i] = -1; d[i] = 2; num[i] = 1; }
        for ( int j = 1; j <= tot && i * prime[j] <= n; ++ j ) 
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) 
            { 
                miu[i * prime[j]] = 0; 
                num[i * prime[j]] = num[i] + 1; 
                d[i * prime[j]] = d[i] / num[i * prime[j]] * (num[i * prime[j]] + 1);
                break ; 
            }
            miu[i * prime[j]] = - miu[i];
            num[i * prime[j]] = 1;
            d[i * prime[j]] = d[i] * 2;
        }
    }
    REP(i, 1, n) for ( int j = i; j <= n; j += i ) f[j] += miu[j / i] * d[i] * d[i];
    REP(p, 1, n) 
    {
        REP(i, 0, n / p) g[p].push_back(0);
        REP(i, 1, n / p) g[p][i] = g[p][i - 1] + d[i] * f[i * p];
    }
    REP(p, 1, n) REP(i, 1, 20) REP(j, 1, 20)
    {
        if ( i * p > n || j * p > n ) continue ;
        h[i][j][p] = h[i][j][p - 1] + miu[p] * d[i] * f[i * p] * d[j] * f[j * p];
    }
    REP(p, 1, n) REP(i, 1, 20) REP(j, 1, 20)
    {
        if ( i * p > n || j * p > n ) continue ;
        h[i][j][p] += h[i - 1][j][p] + h[i][j - 1][p] - h[i - 1][j - 1][p];
    }
    int T; scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d", &n, &m);
        int limit = min(n, m), ans = 0;
        REP(p, 1, min(block, limit))
        {
            if ( !miu[p] ) continue ;
            ans += miu[p] * F(p, n / p) * F(p, m / p);
        }
        for ( int i = block + 1, j; i <= limit; i = j + 1 )
        {
            j = min(n / (n / i), m / (m / i));
            ans += h[n / i][m / i][j] - h[n / i][m / i][i - 1];
        }
        printf("%d\n", (ans % Mod + Mod) % Mod);
    }
    return 0;
}
