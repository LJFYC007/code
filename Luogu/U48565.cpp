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

const LL Mod = 123456789;

LL ans = 0;

inline LL power(LL a, LL b) 
{
    LL r = 1;
    while ( b ) 
    {
        if ( b & 1 ) r = (r * a) % Mod;
        a = (a * a) % Mod;
        b /= 2;
    }
    return r;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    LL k;
    scanf("%lld", &k);
    if ( k == 1 ) printf("1\n"); 
    else printf("%lld\n", power(2, k - 1));
    return 0;
}
