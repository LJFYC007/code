/***************************************************************
	File name: number.cpp
	Author: ljfcnyali
	Create time: 2020年09月05日 星期六 08时58分01秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5010;
const int Mod = 998244353;

int n, m, ans, s[maxn][maxn], p[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
    scanf("%lld%lld", &n, &m); 
    s[0][0] = 1;
    REP(i, 1, m) REP(j, 1, m) s[i][j] = (s[i - 1][j - 1] + s[i - 1][j] * j) % Mod;
    REP(i, 0, m) p[i] = power(2, n - i);

    REP(i, 0, m)
    {
        int x; scanf("%lld", &x);
        int sum = 1, ret = 0;
        REP(k, 0, i)
        {
            ret = (ret + (sum * s[i][k] % Mod) * p[k]) % Mod;
            sum = sum * (n - k) % Mod;
        }
        ans = (ans + x * ret) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
