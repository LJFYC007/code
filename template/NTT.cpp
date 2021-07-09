/***************************************************************
	File name: P3803.cpp
	Author: ljfcnyali
	Create time: 2019年09月27日 星期五 09时45分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define int long long
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 4000010;
const int Mod = 998244353;
const int g = 3;

int a[maxn], b[maxn], r[maxn], n, m;

inline int power(int a, int b)
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = (r * a) % Mod; a = (a * a) % Mod; b >>= 1; }
    return r;
}

inline void NTT(int *f, int inv)
{
    REP(i, 0, n - 1) if ( i < r[i] ) swap(f[i], f[r[i]]);
    for ( int Mid = 1; Mid < n; Mid <<= 1 )
    {
        int tmp = power(g, (Mod - 1) / (Mid << 1));
        if ( inv == -1 ) tmp = power(tmp, Mod - 2);
        for ( int i = 0; i < n; i += (Mid << 1) )
        {
            int sum = 1;
            for ( int j = 0; j < Mid; ++ j, sum = (sum * tmp) % Mod )
            {
                int x = f[i + j], y = (sum * f[i + j + Mid]) % Mod;
                f[i + j] = (x + y) % Mod; f[i + j + Mid] = (x - y + Mod) % Mod;
            }
        }
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 0, n) scanf("%lld", &a[i]); REP(i, 0, m) scanf("%lld", &b[i]);    
    m += n; n = 1;
    while ( n <= m ) n <<= 1;
    REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
    NTT(a, 1); NTT(b, 1);
    // REP(i, 0, n) printf("%lld ", a[i]); puts("");
    // REP(i, 0, n) printf("%lld ", b[i]); puts("");
    REP(i, 0, n - 1) a[i] = (a[i] * b[i]) % Mod;
    NTT(a, -1);
    int inv = power(n, Mod - 2);
    REP(i, 0, m) printf("%lld ", (inv * a[i]) % Mod); puts("");
    return 0;
}
