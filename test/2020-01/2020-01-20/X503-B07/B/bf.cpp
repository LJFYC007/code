/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年01月20日 星期一 08时36分57秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 998244353;
const int op = (Mod + 1) / 2;

int n, k, a[maxn], f[maxn], g[maxn], sum;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
    scanf("%lld%lld", &n, &k);
    REP(i, 1, n) { scanf("%lld", &a[i]); sum += a[i]; }
    sum = power(sum, Mod - 2);
    f[0] = 1;
    REP(o, 1, k)
    {
        REP(i, 0, n) { g[i] = f[i]; f[i] = 0; }
        REP(i, 0, n) REP(j, 1, n)
        {
            int x = i + j; if ( x > n ) x = 2 * n -  x;
            f[x] = (f[x] + ((g[i] * a[j] % Mod) * sum % Mod) * op) % Mod;
            x = i - j; if ( x < 0 ) x = -x;
            f[x] = (f[x] + ((g[i] * a[j] % Mod) * sum % Mod) * op) % Mod;
        }
    }
    REP(i, 0, n) printf("%lld ", f[i]); puts("");
    return 0;
}
