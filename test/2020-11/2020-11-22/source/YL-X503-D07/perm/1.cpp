/***************************************************************
	File name: perm.cpp
	Author: ljfcnyali
	Create time: 2020年11月22日 星期日 11时15分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;
const int Mod = 1e9 + 7;

int T, n, a[maxn], b[maxn], f[maxn][maxn], fac[maxn];

inline int sgn(int x) { return x & 1 ? -1 : 1; }

signed main()
{
    freopen("perm.in", "r", stdin);
    freopen("perm.out", "w", stdout);
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld", &n);
        fac[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
        REP(i, 1, n) scanf("%lld%lld", &a[i], &b[i]);        
        f[0][0] = 1;
        REP(i, 1, n) REP(j, 0, i)
            REP(k, 0, j) f[i][j] = (f[i][j] + (i > k ? f[i - k - 1][j - k] : 1) * (k + 1)) % Mod;

        // REP(i, 1, n) REP(j, 0, i) cout << i << " " << j << " " << f[i][j] << endl;
        f[n][n] = 2;
        int ans = 0;
        // REP(i, 0, n) cout << sgn(i) * fac[n - i] * f[n][i] << endl;
        REP(i, 0, n) ans = (ans + sgn(i) * fac[n - i] * f[n][i]) % Mod;
        printf("%lld\n", (ans + Mod) % Mod);
    }
    return 0;
}
