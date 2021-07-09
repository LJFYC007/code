/***************************************************************
	File name: P3281.cpp
	Author: ljfcnyali
	Create time: 2019年11月04日 星期一 19时07分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 200010;
const int Mod = 20130427;
const int N = 2e5;

int B, n, tmp[maxn], ans, f[maxn], g[maxn], p[maxn], a[maxn];

inline int DFS2(int x, bool opt)
{
    if ( x == n + 1 ) return 1;
    if ( !opt && g[x] ) return g[x];
    int dim = opt ? tmp[x] : 9, ret = 0;
    REP(i, 0, dim) ret = (ret + DFS2(x + 1, opt & (i == dim))) % Mod;
    if ( !opt ) g[x] = ret; return ret;
}

inline int DFS1(int x, bool opt)
{
    if ( x == n + 1 ) return 0;
    if ( !opt && f[x] ) return f[x];
    int dim = opt ? tmp[x] : 9, ret = 0;
    REP(i, 0, dim) 
    {
        int sum = (i * x % Mod) * p[n - x] % Mod;
        a[x] = i;
        REP(j, 1, x) printf("%d", a[j]); printf(" %d %d\n", sum, DFS2(x + 1, opt & (i == dim)));
        ret = (ret + sum * DFS2(x + 1, opt & (i == dim)) + DFS1(x + 1, opt & (i == dim))) % Mod;
    }
    if ( !opt ) f[x] = ret; return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &B);
    int x = 1; p[0] = 1;
    REP(i, 1, N) { x = x * B % Mod; p[i] = (p[i - 1] + x) % Mod; }
    scanf("%lld", &n); REP(i, 1, n) scanf("%lld", &tmp[i]);
    if ( n == 1 && tmp[1] == 0 ) ;
    else
    { 
        int i = n; 
        while ( tmp[i] == 0 && i >= 1 ) { tmp[i] = 9; -- i; } 
        -- tmp[i]; 
    }
    ans = DFS1(1, 1);
    scanf("%lld", &n); REP(i, 1, n) scanf("%lld", &tmp[i]);
    mem(f); mem(g);
    ans = (DFS1(1, 1) - ans) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
