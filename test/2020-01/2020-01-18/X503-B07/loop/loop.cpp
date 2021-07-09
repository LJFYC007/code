/***************************************************************
	File name: loop.cpp
	Author: ljfcnyali
	Create time: 2020年01月18日 星期六 09时10分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e7 + 10;
const int seed = 233;
const int Mod = 1e9 + 7;

char s[maxn];
int n, p[maxn], Hash[maxn], inv[maxn], Max;
bool ans[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int Get(int L, int R)
{
    if ( L > R ) return -1;
    int x = (Hash[R] - Hash[L - 1]) * inv[L - 1] % Mod;
    return (x + Mod) % Mod;
}

/*
 * rrgrrg
 * r rgr rg
 */

inline void Solve(int L, int R)
{
    REP(i, L, R) Hash[i - L + 1] = (Hash[i - L] + (s[i] - 'a') * p[i - L]) % Mod;
    R = R - L + 1; Max = max(Max, R);
    REP(i, 1, R)
    {
        int x = Get(1, R - i), y = Get(i + 1, R);
        if ( x != y && x != -1 ) ans[i] = true;
    }
}

signed main()
{
    freopen("loop.in", "r", stdin);
    freopen("loop.out", "w", stdout);
    p[0] = 1; REP(i, 1, maxn - 10) p[i] = p[i - 1] * seed % Mod;
    inv[0] = 1; int x = power(seed, Mod - 2); REP(i, 1, maxn - 10) inv[i] = inv[i - 1] * x % Mod;
    while ( ~scanf("%s", s) )
    {
        n = str(s); Max = -1;
        REP(i, 0, n - 1) s[i + n] = s[i];  
        n += n;
        REP(i, 0, n - 1) ans[i] = false;
        int las = 0;
        REP(i, 1, n - 1) if ( s[i] == s[i - 1] )
        {
            Solve(las, i - 1);
            las = i;
        }
        Solve(las, n - 1);
        // printf("%lld\n", Max);
        for ( int i = n / 2 - 1; i >= 0; -- i ) printf("%d", ans[i]); puts("");
        // REP(i, n / 21) printf("%d", i > Max ? 0 : ans[i]); puts("");
    }
    return 0;
}
