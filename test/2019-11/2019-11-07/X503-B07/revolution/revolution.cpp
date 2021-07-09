/***************************************************************
	File name: revolution.cpp
	Author: ljfcnyali
	Create time: 2019年11月07日 星期四 10时20分33秒
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
const int Mod = 998244353;

int n, ans[maxn], w[5][5], p[maxn][5];

inline int power(int a, int b)
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; }
    return r;
}

signed main()
{
    freopen("revolution.in", "r", stdin);
    freopen("revolution.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) REP(j, 1, 4) scanf("%lld", &p[i][j]);
    REP(i, 1, 4) REP(j, 1, 4) scanf("%lld", &w[i][j]);
    int x = power(n, Mod - 2);
    REP(a, 0, n) REP(b, 0, n - a) REP(c, 0, n - a - b) REP(d, 0, n - a - b - c)
    {
        int pos = -1;
        if ( a >= n / 2 ) pos = 1; 
        else if ( b >= n / 2 ) pos = 2;
        else if ( c >= n / 2 ) pos = 3;
        else if ( d >= n / 2 ) pos = 4;
        if ( pos == -1 ) continue ;
        int aa = a * x % Mod, bb = b * x % Mod, cc = c * x % Mod, dd = d * x % Mod;
        REP(i, 1, n)
        {
            int A = p[i][1] * aa % Mod * w[pos][1] % Mod;
            int B = p[i][2] * bb % Mod * w[pos][2] % Mod;
            int C = p[i][3] * cc % Mod * w[pos][3] % Mod;
            int D = p[i][4] * dd % Mod * w[pos][4] % Mod;
            ans[i] = (ans[i] + A + B + C + D) % Mod;
        }
    }
    REP(i, 1, n) printf("%lld\n", ans[i]); puts("");
    return 0;
}

