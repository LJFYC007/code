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
const int maxn = 1010;

LL n, k, a[maxn][maxn], r[maxn][maxn], c[maxn][maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &k);
    REP(i, 1, n) REP(j, 1, n) { scanf("%lld", &a[i][j]); r[i][j] = a[i][j]; }
    k --;
    while ( k ) 
    {
        if ( k & 1 ) 
        {
            mem(c);
            REP(i, 1, n)
                REP(j, 1, n)
                    REP(o, 1, n)
                    {
                        c[i][j] += r[i][o] * a[o][j];
                        c[i][j] %= Mod; 
                    }            
            REP(i, 1, n) REP(j, 1, n) r[i][j] = c[i][j];
        }
        k /= 2;
        mem(c);
        REP(i, 1, n)
            REP(j, 1, n)
                REP(o, 1, n)
                {
                    c[i][j] += a[i][o] * a[o][j];
                    c[i][j] %= Mod;  
                }
        REP(i, 1, n) REP(j, 1, n) a[i][j] = c[i][j];
    }
    REP(i, 1, n)
    {
        REP(j, 1, n)
            printf("%lld ", r[i][j]);
        puts("");
    }
    return 0;
}
