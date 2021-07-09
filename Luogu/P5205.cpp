/***************************************************************
	File name: P5205.cpp
	Author: ljfcnyali
	Create time: 2019年12月16日 星期一 10时20分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 4e5 + 10;
const int Mod = 998244353;

int inv, r[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void NTT(int f[], int n, int opt)
{
    REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
    REP(i, 0, n - 1) if ( i < r[i] ) swap(f[i], f[r[i]]);
    for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
    {
        int tmp = power(3, (Mod - 1) / (Mid << 1));
        if ( opt == -1 ) tmp = power(tmp, Mod - 2);
        for ( int i = 0; i < n; i += (Mid << 1) )
        {
            int sum = 1;
            for ( int j = 0; j < Mid; ++ j, sum = sum * tmp % Mod )
            {
                int x = f[i + j], y = f[i + j + Mid] * sum % Mod;
                f[i + j] = (x + y) % Mod; f[i + j + Mid] = (x - y) % Mod;
            }
        }
    }
    if ( opt == -1 ) 
    {
        int x = power(n, Mod - 2);
        REP(i, 0, n - 1) f[i] = f[i] * x % Mod;
    }
}

inline void Inv(int f[], int g[], int n)
{
    if ( n == 1 ) { g[0] = power(f[0], Mod - 2); return ; }
    int len = n + 1 >> 1;
    Inv(f, g, len);
    int m = 1; while ( m < (n << 1) ) m <<= 1;
    static int a[maxn];
    copy(f, f + n, a); fill(a + n, a + m, 0); fill(g + len, g + m, 0);
    NTT(a, m, 1); NTT(g, m, 1); 
    REP(i, 0, m - 1) g[i] = g[i] * ((2 - a[i] * g[i]) % Mod) % Mod;
    NTT(g, m, -1); fill(g + n, g + m, 0);
}

inline void Sqrt(int f[], int g[], int n)
{
    if ( n == 1 ) { g[0] = 1; return ; }
    int len = n + 1 >> 1;
    Sqrt(f, g, len);
    int m = 1; while ( m < (n << 1) ) m <<= 1;
    static int a[maxn], g0[maxn];
    Inv(g, g0, n); 
    copy(f, f + n, a); fill(a + n, a + m, 0);
    NTT(a, m, 1); NTT(g, m, 1); NTT(g0, m, 1);
    REP(i, 0, m - 1) g[i] = inv * (g[i] + (a[i] * g0[i] % Mod)) % Mod;
    NTT(g, m, -1); fill(g + n, g + m, 0);
}

int f[maxn], g[maxn], n;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n); inv = power(2, Mod - 2);
    REP(i, 0, n - 1) scanf("%lld", &f[i]);
//    Inv(f, g, n);
    Sqrt(f, g, n);
    REP(i, 0, n - 1) printf("%lld ", (g[i] + Mod) % Mod); puts("");
    return 0;
}
