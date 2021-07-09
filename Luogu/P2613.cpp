/***************************************************************
	File name: P2613.cpp
	Author: ljfcnyali
	Create time: 2019年08月29日 星期四 15时33分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

LL a, b, Mod = 19260817;

inline void read(LL &x)
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) x = (x * 10 + c - '0') % Mod, c = getchar();
}

inline LL power(LL a, LL b)
{
    LL r = 1;
    while ( b ) { if ( b & 1 ) r = (r * a) % Mod; a = (a * a) % Mod; b >>= 1; }
    return r;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    read(a); read(b);
    if ( b == 0 ) puts("Angry!");
    else printf("%lld\n", (a * power(b, Mod - 2)) % Mod);
    return 0;
}
