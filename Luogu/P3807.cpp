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

LL p, T, f[100000];

inline LL power(LL a, LL b)
{
    LL r = 1;
    while ( b ) 
    {
        if ( b & 1 ) r = (r * a) % p;
        a = (a * a) % p;
        b /= 2;
    }
    return r;
}

inline LL C(LL n, LL m)
{
    if ( m > n ) return 0;
    return f[n] * power((f[m] * f[n - m]) % p, p - 2) % p;
}

inline LL Lucas(LL n, LL m)
{
    if ( !m ) return 1;
    return (C(n % p, m % p) * Lucas(n / p, m / p)) % p;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &T);
    while ( T -- )
    {
        LL n, m;
        scanf("%lld%lld%lld", &n, &m, &p);
        f[0] = 1;
        REP(i, 1, p) f[i] = (f[i - 1] * i) % p;
        printf("%lld\n", Lucas(n + m, m));
    }
    return 0;
}
