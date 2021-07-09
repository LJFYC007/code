/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年11月05日 星期四 15时16分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
#define int long long

const int maxn = 110;
const int Mod = 998244353;

int n, m, f[maxn][maxn][maxn];

inline int Solve(int n, int m, int k)
{
    if ( n <= 0 ) return k == 1;
    if ( m == 0 ) return k == 0;
    if ( k == 0 ) return 0;
    if ( n == 1 ) return k <= m;
    if ( f[n][m][k] != -1 ) return f[n][m][k];
    int ret = (k == 1);
    REP(x, 1, n) REP(y, x, n) REP(i, 1, k)
    {
        int val = Solve(n - y - 1, m, k - i);
        ret = (ret + val * Solve(y - x + 1, m - 1, i)) % Mod;
    }
    f[n][m][k] = ret; return ret;
}

signed main()
{
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    memset(f, -1, sizeof(f));
    int ans = 0;
    REP(i, 1, n * m) ans = (ans + (Solve(n, m, i) - Solve(n, m - 1, i)) * i * i) % Mod;
    printf("%lld\n", ans);
    return 0;
}
