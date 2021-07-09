/***************************************************************
	File name: satellite.cpp
	Author: ljfcnyali
	Create time: 2020年11月20日 星期五 15时23分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;

int n, q, w, h, Mod, a, b, ans[maxn];
int f[2010][2010], g[2010];
vector<int> Q[2010][2010];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
    freopen("satellite.in", "r", stdin);
    freopen("satellite.out", "w", stdout);
    scanf("%lld%lld%lld%lld%lld%lld%lld", &n, &q, &w, &h, &Mod, &a, &b);
    REP(i, 1, n) { int h, x, y; scanf("%lld%lld%lld", &h, &x, &y); f[x][y] += h; }
    REP(i, 1, q) { int x, y; scanf("%lld%lld", &x, &y); Q[x][y].push_back(i); }
    REP(i, 1, w)
    {
        int val = 0; REP(j, 1, w) val = (val + f[j][1] * power(a, abs(j - i))) % Mod;
        REP(j, 1, h)
        {
            for ( auto it : Q[i][j] ) ans[it] = (ans[it] + val) % Mod;
            val = val * b % Mod;
            REP(k, 1, w) val = (val + f[k][j + 1] * power(a, abs(k - i))) % Mod;
        }
        val = 0; 
        for ( int j = h; j >= 1; -- j ) 
        {
            for ( auto it : Q[i][j] ) ans[it] = (ans[it] + val) % Mod;
            REP(k, 1, w) val = (val + f[k][j] * power(a, abs(k - i))) % Mod;
            val = val * b % Mod;
        }
    }
    REP(i, 1, q) printf("%lld\n", (ans[i] + Mod) % Mod);
    return 0;
}
