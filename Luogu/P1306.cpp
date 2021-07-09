#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int minn(T a, T b) { return a < b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define min minn
#define abs abss

const int Mod = 100000000;

LL r[3][3], a[3][3], n, m, c[3][3];

inline LL gcd(LL a, LL b) 
{
    return b ? gcd(b, a % b) : a;
}

inline void power(LL b)
{
    while ( b ) 
    {
        if ( b % 2 == 1 ) 
        {
            c[1][1] = r[1][1] * a[1][1] + r[1][2] * a[2][1]; c[1][1] %= Mod;
            c[1][2] = r[1][1] * a[1][2] + r[1][2] * a[2][2]; c[1][2] %= Mod;
            c[2][1] = r[2][1] * a[1][1] + r[2][2] * a[2][1]; c[2][1] %= Mod;
            c[2][2] = r[2][1] * a[1][2] + r[2][2] * a[2][2]; c[2][2] %= Mod;
            r[1][1] = c[1][1]; r[1][2] = c[1][2]; r[2][1] = c[2][1]; r[2][2] = c[2][2];
        }
        b /= 2;
        c[1][1] = a[1][1] * a[1][1] + a[1][2] * a[2][1]; c[1][1] %= Mod;
        c[1][2] = a[1][1] * a[1][2] + a[1][2] * a[2][2]; c[1][2] %= Mod;
        c[2][1] = a[2][1] * a[1][1] + a[2][2] * a[2][1]; c[2][1] %= Mod;
        c[2][2] = a[2][1] * a[1][2] + a[2][2] * a[2][2]; c[2][2] %= Mod;
        a[1][1] = c[1][1]; a[1][2] = c[1][2]; a[2][1] = c[2][1]; a[2][2] = c[2][2];
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    n = gcd(n, m);
    a[1][1] = 1; a[1][2] = 1; a[2][1] = 1; a[2][2] = 0;
    r[1][1] = 1; r[1][2] = 1; r[2][1] = 1; r[2][2] = 0;
    if ( n <= 3 ) 
    {
        if ( n == 3 ) printf("2\n");
        else printf("1\n");
        return 0;
    }
    power(n - 3);
    printf("%lld\n", (r[1][1] + r[2][1]) % Mod);
    return 0;
}
