/***************************************************************
	File name: CF983E.cpp
	Author: ljfcnyali
	Create time: 2020年10月27日 星期二 10时09分46秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 7860;
const int Mod = 1e9 + 7;

int R, a[5], p[5], f[maxn][maxn], n, ans[maxn];
int dt[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
vector<int> g[maxn];
map<pii, int> Map;
bitset<maxn> vis[maxn];

inline LL power(LL a, int b) { LL r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &R); 
    REP(i, 1, 4) { scanf("%d", &a[i]); a[0] += a[i]; }
    REP(i, 1, 4) p[i] = a[i] * power(a[0], Mod - 2) % Mod;
    REP(x, -R, R) REP(y, -R, R)
    {
        if ( x * x + y * y > R * R ) continue ;
        Map[pii(x, y)] = ++ n;
    }
    REP(x, -R, R) REP(y, -R, R)
    {
        if ( x * x + y * y > R * R ) continue ;
        int pos = Map[pii(x, y)]; f[pos][pos] = 1; g[pos].push_back(pos);
        REP(i, 0, 3)
        {
            int u = x + dt[i][0], v = y + dt[i][1];
            if ( !Map.count(pii(u, v)) ) continue ;
            int t = Map[pii(u, v)]; f[pos][t] = -p[i + 1]; g[pos].push_back(t);
        }
        f[pos][0] = -1; g[pos].push_back(0);
        for ( auto it : g[pos] ) vis[pos][it] = true;
    }

    REP(i, 1, n) REP(j, i + 1, min(i + 2 * R, n))
    {
        LL tmp = f[j][i] * power(f[i][i], Mod - 2) % Mod;
        if ( !tmp ) continue ;
        for ( auto it : g[i] ) 
        {
            int y = (f[j][it] - tmp * f[i][it]) % Mod;
            if ( !vis[j][it] && y ) { g[j].push_back(it); vis[j][it] = true; }
            f[j][it] = y; 
        }
    }
    ans[0] = 1;
    for ( int i = n; i >= 1; -- i ) 
    {
        int sum = 0;
        for ( auto it : g[i] ) sum = (sum + 1ll * ans[it] * f[i][it]) % Mod;
        ans[i] = -sum * power(f[i][i], Mod - 2) % Mod;
    }
    printf("%d\n", (ans[Map[pii(0, 0)]] + Mod) % Mod);
    return 0;
}
