/***************************************************************
	File name: P4564.cpp
	Author: ljfcnyali
	Create time: 2019年11月08日 星期五 19时55分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 210;
const int maxm = 200010;
const int Mod = 998244353;

int n, a[maxn], f[maxn][maxn], m;

inline int power(int a, int b) 
{ 
    int r = 1; 
    while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } 
    return r; 
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) { scanf("%lld", &a[i]); f[i][0] = 1; }
    scanf("%lld", &m);
    REP(i, 1, m)
    {
        int opt; scanf("%lld", &opt);
        if ( opt == 0 ) 
        {
            int x, u, v; scanf("%lld%lld%lld", &x, &u, &v);
            u = u * power(v, Mod - 2) % Mod;
            for ( int j = a[x] - 1; j >= 1; -- j ) f[x][j] = (f[x][j] * (1 - u) + f[x][j - 1] * u) % Mod;
            f[x][0] = f[x][0] * (1 - u) % Mod;
            continue ;
        }
        int k; scanf("%lld", &k);
        REP(i, 1, k) { int x = 0; scanf("%lld", &x); }
    }
    REP(i, 1, n) 
    {
        int ret = 0;
        REP(j, 0, a[i] - 1) ret = (ret + f[i][j] * (a[i] - j)) % Mod;
        printf("%lld ", (ret + Mod) % Mod);
    }
    puts("");
    return 0;
}
