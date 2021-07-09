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

const int maxn = 40100;
const int Mod = 1e9 + 7;

int n, m, a[maxn], f[110][maxn], sum1, sum2;

signed main()
{
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) scanf("%lld", &a[i]);

    mem(f);
    REP(i, 0, (1 << m) - 1) if ( (a[1] | i) == a[1] ) f[1][i] = 1;
    REP(i, 2, n) REP(j, 0, (1 << m) - 1)
        REP(k, 0, (1 << m) - 1)
            if ( (a[i] | k) == a[i] && (a[i - 1] & j) <= (a[i] & k) )
                f[i][k] = (f[i][k] + f[i - 1][j]) % Mod;
    REP(i, 0, (1 << m) - 1) sum1 = (sum1 + f[n][i]) % Mod;

    mem(f);
    REP(i, 0, (1 << m) - 1) if ( (a[1] & i) == 0 ) f[1][i] = 1;
    REP(i, 2, n) REP(j, 0, (1 << m) - 1)
        REP(k, 0, (1 << m) - 1)
            if ( (a[i] & k) == 0 && (a[i - 1] | j) >= (a[i] | k) )
                f[i][k] = (f[i][k] + f[i - 1][j]) % Mod;
    REP(i, 0, (1 << m) - 1) sum2 = (sum2 + f[n][i]) % Mod;
    cerr << sum2 << endl;

    printf("%lld\n", sum1 * sum2 % Mod);
    return 0;
}
