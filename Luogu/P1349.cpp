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

int a[3][3], n, Mod, p, q, a1, a2, r[3][3], c[3][3];

inline void power(int b)
{   
    while ( b )
    {
        if ( b & 1 )
        {
            c[1][1] = r[1][1] * a[1][1] + r[1][2] * a[1][2]; c[1][1] %= Mod;
            c[1][2] = r[1][1] * a[1][2] + r[1][2] * a[2][2]; c[1][2] %= Mod;
            c[2][1] = r[2][1] * a[1][1] + r[2][2] * a[1][2]; c[2][1] %= Mod;
            c[2][2] = r[2][1] * a[1][2] + r[2][2] * a[2][2]; c[2][2] %= Mod;
            r[1][1] = c[1][1]; r[1][2] = c[1][2]; r[2][1] = c[2][1]; r[2][2] = c[2][2];
        }
        b /= 2;
        c[1][1] = a[1][1] * a[1][1] + a[1][2] * a[1][2]; c[1][1] %= Mod;
        c[1][2] = a[1][1] * a[1][2] + a[1][2] * a[2][2]; c[1][2] %= Mod;
        c[2][1] = a[2][1] * a[1][1] + a[2][2] * a[1][2]; c[2][1] %= Mod;
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
    scanf("%d%d%d%d%d%d", &p, &q, &a1, &a2, &n, &Mod);    
    a[1][1] = p; a[1][2] = q;
    a[2][1] = 1; a[2][2] = 0;    
    r[1][1] = p; r[1][2] = q;
    r[2][1] = 1; r[2][2] = 0;
    if ( n == 1 ) printf("%d\n", a1);
    else if ( n == 2 ) printf("%d\n", a2);
    else if ( n == 3 ) printf("%d\n", a1 * p + a2 * q);
    else
    {
        power(n - 3);
        printf("%d\n", (a1 * r[1][1] + a2 * r[1][2]) % Mod);
    }
    return 0;
}
