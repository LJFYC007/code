/***************************************************************
	File name: sequence.cpp
	Author: ljfcnyali
	Create time: 2020年07月15日 星期三 11时18分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 110;
const int Mod = 1e9 + 7;

int n, m, a[maxn], f[maxn][maxn][31], sum1, sum2, g[maxn][40024];

inline int Solve1(int l, int r, int x)
{
    if ( l > r || !x ) return 1;
    if ( f[l][r][x] != -1 ) return f[l][r][x];
    if ( l == r ) 
    {
        int ret = 1;
        REP(i, 1, x) if ( (a[l] >> i - 1) & 1 ) ret = ret * 2 % Mod;
        f[l][r][x] = ret; return ret;
    }
    int ret = 0;
    for ( int j = r; j >= l - 1; -- j ) 
    {
        ret = (ret + Solve1(l, j, x - 1) * Solve1(j + 1, r, x - 1)) % Mod;
        if ( !((a[j] >> x - 1) & 1) ) break ;
    }
    f[l][r][x] = ret; return ret;
}

inline int Solve2(int l, int r, int x)
{
    if ( l > r || !x ) return 1;
    if ( f[l][r][x] != -1 ) return f[l][r][x];
    if ( l == r ) 
    {
        int ret = 1;
        REP(i, 1, x) if ( !((a[l] >> i - 1) & 1) ) ret = ret * 2 % Mod;
        f[l][r][x] = ret; return ret;
    }
    int ret = 0;
    for ( int j = r; j >= l - 1; -- j ) 
    {
        ret = (ret + Solve2(l, j, x - 1) * Solve2(j + 1, r, x - 1)) % Mod;
        if ( (a[j] >> x - 1) & 1 ) break ;
    }
    f[l][r][x] = ret; return ret;
}

signed main()
{
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) scanf("%lld", &a[i]);

    memset(f, -1, sizeof(f)); sum1 = Solve1(1, n, m); 
    memset(f, -1, sizeof(f)); sum2 = Solve2(1, n, m);

    printf("%lld\n", sum1 * sum2 % Mod);
    return 0;
}
