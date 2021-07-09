/***************************************************************
	File name: c.cpp
	Author: ljfcnyali
	Create time: 2019年10月16日 星期三 10时52分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define inv(x) power(x, Mod - 2)
typedef long long LL;

const int Mod = 1e9 + 7;
const int maxn = 5010;

int n, m, a[maxn][maxn], ans, p[maxn], p1[maxn], p2[maxn];

inline int power(int a, int b)
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; }
    return r;
}

inline int C(int n, int m)
{
    int sum = (p1[n] * p2[m] % Mod) * p2[n - m] % Mod;
    return sum;
}

namespace Subtask1
{
    inline int main()
    {
        REP(i, 1, n) REP(j, 1, i)
        {
            int x = (i + j % 2 == 1) ? a[i][j] : Mod - a[i][j];
            ans = (ans + x * x) % Mod;
        }
        printf("%lld\n", ans);
        return 0;
    }
}

signed main()
{
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) p[i] = inv(power(i, m));
    p1[0] = 1; REP(i, 1, n) p1[i] = p1[i - 1] * i % Mod;
    REP(i, 0, n) p2[i] = inv(p1[i]);
    REP(i, 1, n) 
    {
        REP(j, 1, i)
            a[i][j] = C(i, j) * p[j] % Mod;
        a[i][n + i] = 1;
    }
    if ( m == 0 ) return Subtask1 :: main();
    REP(i, 1, n)
    {
        REP(j, i, n) if ( a[j][i] ) { REP(k, 1, n + n) swap(a[i][k], a[j][k]); break ; }
        int x = inv(a[i][i]);
        REP(j, i, n + n) a[i][j] = a[i][j] * x % Mod;
        REP(j, 1, n) if ( j != i )
        {
            int y = a[j][i];
            REP(k, i, n + n) a[j][k] = (a[j][k] - y * a[i][k] % Mod + Mod) % Mod;
        }
    }
    REP(i, 1, n) REP(j, n + 1, n + n) ans = (ans + a[i][j] * a[i][j]) % Mod;
    printf("%lld\n", ans);
    return 0;
}

