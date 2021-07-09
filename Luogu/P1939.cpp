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

const int Mod = 1000000007;

LL r[4][4], a[4][4], T, n, c[4][4];

inline void power(LL b)
{
    while ( b ) 
    {
        if ( b & 1 )
        {
            mem(c);
            REP(i, 1, 3)
                REP(j, 1, 3)
                    REP(k, 1, 3)
                    {
                        c[i][j] += r[i][k] * a[k][j];
                        c[i][j] %= Mod;
                    }
            REP(i, 1, 3)
                REP(j, 1, 3)
                    r[i][j] = c[i][j];
        }
        b /= 2;
        mem(c);
        REP(i, 1, 3)
            REP(j, 1, 3)
                REP(k, 1, 3)
                {
                    c[i][j] += a[i][k] * a[k][j];
                    c[i][j] %= Mod;
                }
        REP(i, 1, 3)
            REP(j, 1, 3)
                a[i][j] = c[i][j];
    }
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
        scanf("%lld", &n);
        mem(a); mem(r);
        a[1][1] = a[3][1] = a[1][2] = a[2][3] = 1;
        r[1][1] = r[3][1] = r[1][2] = r[2][3] = 1;
        if ( n <= 3 ) { printf("1\n"); continue ; }
        power(n - 3);
//        REP(i, 1, 3) { REP(j, 1, 3) printf("%lld ", r[i][j]); puts(""); }
//        puts("");
        printf("%lld\n", (r[1][1] + r[2][1]) % Mod);
    }
    return 0;
}
