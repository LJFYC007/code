/***************************************************************
	File name: LibreOJ_6502.cpp
	Author: ljfcnyali
	Create time: 2020年11月12日 星期四 19时34分00秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long 
typedef long long LL;

const int maxn = 2010;
const int INF = 0x3f3f3f3f;
const int Mod = 1e9 + 7;

int f[maxn][maxn], n, m, a[maxn], g[maxn][maxn];

inline void Solve(int x, int l, int r)
{
    if ( l == r ) 
    { 
        f[x][0] = f[x][1] = 0;
        g[x][0] = g[x][1] = 1; 
        return ; 
    }
    if ( a[l] + a[r] >= m ) 
    {
        Solve(x + 1, l, r - 1);
        REP(i, 0, n) 
        {
            if ( i >= 1 ) 
            {
                int val1 = f[x + 1][i - 1] + r - l - i + 1;
                if ( val1 > f[x][i] ) { f[x][i] = val1; g[x][i] = g[x + 1][i - 1]; }
                else if ( val1 == f[x][i] ) g[x][i] = (g[x][i] + g[x + 1][i - 1]) % Mod;
            }
            int val2 = f[x + 1][i] + i;
            if ( val2 > f[x][i] ) { f[x][i] = val2; g[x][i] = g[x + 1][i]; }
            else if ( val2 == f[x][i] ) g[x][i] = (g[x][i] + g[x + 1][i]) % Mod;
        }
    }
    else 
    {
        Solve(x + 1, l + 1, r);
        REP(i, 0, n) 
        {
            if ( i >= 1 ) 
            {
                int val1 = f[x + 1][i - 1];
                if ( val1 > f[x][i] ) { f[x][i] = val1; g[x][i] = g[x + 1][i - 1]; }
                else if ( val1 == f[x][i] ) g[x][i] = (g[x][i] + g[x + 1][i - 1]) % Mod;
            }
            int val2 = f[x + 1][i];
            if ( val2 > f[x][i] ) { f[x][i] = val2; g[x][i] = g[x + 1][i]; }
            else if ( val2 == f[x][i] ) g[x][i] = (g[x][i] + g[x + 1][i]) % Mod;
        }
    }
    // cout << l << " " << r << endl;
    // REP(i, 0, n) cout << f[x][i] << " "; cout << endl;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 0, n) REP(j, 0, n) f[i][j] = -INF;
    REP(i, 1, n) scanf("%lld", &a[i]); sort(a + 1, a + n + 1);  
    Solve(1, 1, n);
    int ans = -INF, num = 0;
    REP(i, 0, n)
    {
        if ( f[1][i] > ans ) { ans = f[1][i]; num = g[1][i]; }
        else if ( f[1][i] == ans ) num = (num + g[1][i]) % Mod;
    }
    printf("%lld %lld\n", ans, num);
    return 0;
}
