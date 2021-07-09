/***************************************************************
	File name: CF662C.cpp
	Author: ljfcnyali
	Create time: 2020年01月16日 星期四 10时53分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 998244353;

inline void FWT(int *f, int n, int opt)
{
    opt = opt == 1 ? 1 : (Mod + 1) / 2; 
    for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
       for ( int i = 0; i < n; i += (Mid << 1) ) 
            REP(j, 0, Mid - 1)
            {
                int x = f[i + j], y = f[i + Mid + j];
                f[i + j] = (x + y) * opt % Mod; f[i + Mid + j] = (x - y) * opt % Mod;
            }
}

int n, m, h[maxn << 2], g[maxn << 2], f[maxn << 2], ans, len, a[30][100010];
char s[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    len = 1 << n;
    REP(i, 1, n) { scanf("%s", s + 1); REP(j, 1, m) a[i][j] = s[j] - '0'; }
    REP(i, 0, len - 1)
    {
        REP(j, 0, n - 1) h[i] += (i >> j) & 1;
        h[i] = min(h[i], n - h[i]);
    }
    REP(i, 1, m) 
    {
        int ret = 0;
        REP(j, 1, n) if ( a[j][i] ) ret += 1 << j - 1;    
        ++ g[ret];
    }
    // REP(i, 0, len - 1) printf("%lld ", h[i]); puts("");
    // REP(i, 0, len - 1) printf("%lld ", g[i]); puts("");
    FWT(h, len, 1); FWT(g, len, 1);
    REP(i, 0, len - 1) f[i] = h[i] * g[i] % Mod;
    FWT(f, len, -1);
    ans = 0x3f3f3f3f;
    REP(i, 0, len - 1) ans = min(ans, (f[i] + Mod) % Mod);
    // REP(i, 0, len - 1) printf("%lld ", (f[i] + Mod) % Mod); puts("");
    printf("%lld\n", ans);
    return 0;
}
