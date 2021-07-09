/***************************************************************
	File name: P4727.cpp
	Author: ljfcnyali
	Create time: 2020年07月20日 星期一 20时32分38秒
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
const int Mod = 997;

int n, ans, a[maxn], inv[maxn], f[110][110];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void DFS(int n, int last, int m, int sum)
{
    if ( !n ) 
    {
        int ret = 0;
        REP(i, 1, m) ret += a[i] / 2;
        REP(i, 1, m) REP(j, 1, i - 1) ret += f[a[i]][a[j]];
        ret = power(2, ret) % Mod;
        REP(i, 1, m) ret = ret * inv[a[i]] % Mod;
        ret = ret * sum % Mod;
        ans = (ans + ret) % Mod; return ;
    }
    if ( last > n ) return ; 
    ++ last; int x = 1;
    for ( int i = 0; i <= n; i += last ) 
    {
        DFS(n - i, last, m, sum * x % Mod);
        a[++ m] = last; 
        x = x * inv[(i / last) + 1] % Mod;
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) inv[i] = power(i, Mod - 2);
    REP(i, 1, n) REP(j, 1, n) f[i][j] = __gcd(i, j);
    DFS(n, 0, 0, 1);
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
