/***************************************************************
	File name: game.cpp
	Author: ljfcnyali
	Create time: 2019年07月08日 星期一 10时55分57秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const LL Mod = 1e9 + 7;
const int maxn = 200010;

LL b, w, p[maxn], jc[maxn], x, y;

inline LL power(LL a, LL b)
{
    LL r = 1;
    while ( b ) 
    {
        if ( b & 1 ) r = (r * a) % Mod;
        a = (a * a) % Mod; b >>= 1;
    }
    return r;
}

inline LL ny(LL x) { return power(x, Mod - 2); }

inline LL C(LL n, LL m)
{
    if ( n > m ) return 0;
    if ( !n ) return 1;
    return ((jc[m] * ny(jc[n]) % Mod) * ny(jc[m - n])) % Mod;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
#endif
    scanf("%lld%lld", &b, &w);   
    jc[0] = 1; REP(i, 1, w + b) jc[i] = jc[i - 1] * i % Mod;
    p[0] = 1; REP(i, 1, w + b) p[i] = p[i - 1] * 2 % Mod;
    REP(i, 1, w + b)
    {
        printf("%lld\n", (((1 - x - y) % Mod + Mod) % Mod * ny(2) + y) % Mod);
        x = (x + C(b - 1, i - 1) * ny(p[i])) % Mod;
        y = (y + C(w - 1, i - 1) * ny(p[i])) % Mod;
    }
    return 0;
}

/*
 * 2 0 
 * 1 1
 * 1 0
 * 0 1
 * 0 0 
 */
