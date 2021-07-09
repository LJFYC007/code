/***************************************************************
	File name: jdt.cpp
	Author: ljfcnyali
	Create time: 2020年05月02日 星期六 10时03分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e4 + 10;
const int Mod = 1e9 + 7;

int g[maxn], n, m, ans, k, fac[maxn], p[maxn], a[maxn], prime[maxn], f[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int Solve()
{
    int ret = 1, sum = 1;
    REP(i, 1, m) 
    {
        int x = power(fac[p[i]], a[i]) * fac[a[i]] % Mod;
        sum = sum * x % Mod;
        REP(o, 1, a[i]) ret = (ret * fac[p[i] - 1] % Mod) * ((p[i] & 1) ? 1 : -1);
    }
    ret = ret * power(sum, Mod - 2) % Mod;
    mem(f); f[0] = 1;
    REP(i, 1, m) REP(o, 1, a[i]) REP(j, p[i], n) f[j] = (f[j] + f[j - p[i]]) % Mod; 
    REP(i, 1, n)
    {
        if ( !prime[i] ) continue ;
        ret = ret * f[prime[i]] % Mod; 
    }
    return ret;
}

inline void DFS(int x, int las, int sum)
{
    if ( sum == 0 ) { m = x - 1; ans = (ans + Solve()) % Mod; return ; }
    REP(i, las + 1, sum) 
    {
        int num = 1;
        while ( num * i <= sum ) 
        {
            a[x] = num; p[x] = i;
            DFS(x + 1, i, sum - num * i);
            ++ num;
        }
    }
}

signed main()
{
    freopen("jdt.in", "r", stdin);
    freopen("jdt.out", "w", stdout);
    scanf("%lld%lld", &n, &k);
    fac[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    REP(i, 1, n)
    {
        int x = i;
        for ( int j = 2; j * j <= x; ++ j ) 
            while ( x % j == 0 ) { ++ prime[j]; x /= j; }
        if ( x > 1 ) ++ prime[x];
    }   
    DFS(1, 0, k);
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
