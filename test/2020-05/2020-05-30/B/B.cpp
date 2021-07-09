/***************************************************************
    File name: B.cpp
    Author: ljfcnyali
    Create time: 2020年06月01日 星期一 14时46分11秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;
 
const int maxn = 1010;
const int INF = 1e18;
 
int dig[maxn], T, n, s, x, f[maxn][maxn];
 
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld%lld", &n, &s, &x);
        if ( n == 1 ) { if ( s != x ) puts("-1"); else printf("%lld\n", s); continue ; }
        if ( s < x || s % 2 != x % 2 ) { puts("-1"); continue ; } 
        REP(i, 0, 59) dig[i] = ((x >> i) & 1) + 2 * ((((s - x) / 2) >> i) & 1);
        if ( n == 2 ) 
        {
            int a = 0, b = 0;    
            for ( int i = 59; i >= 0; -- i ) 
            {
                if ( dig[i] == 3 ) { puts("-1"); goto Next; }
                if ( dig[i] == 1 ) b |= (1ll << i);
                if ( dig[i] == 2 ) a |= (1ll << i), b |= (1ll << i);
                if ( a < b ) swap(a, b);
            }
            if ( a + b != s || (a ^ b) != x ) puts("-1");
            else printf("%lld\n", max(a, b));
Next : ;
            continue ;
        }
 
        int L = 0, R = s + 1, ans = -1;
        while ( L <= R ) 
        {
            int Mid = L + R >> 1;
            REP(i, 0, 60) REP(j, 0, 70) f[i][j] = INF;
            f[60][0] = 0;
            for ( int i = 60; i >= 1; -- i ) REP(j, 0, min(n, 70ll))
            {
                if ( f[i][j] == INF ) continue ;
                if ( j >= 3 && f[i][j] == 0 ) { R = ans = Mid - 1; goto finish ; }
                int x = (Mid >> i - 1) & 1, num = dig[i - 1] + f[i][j];
                if ( x == 0 ) 
                {
                    int val = 0;
                    while ( num > j ) { num -= 2; val += 4; }
                    if ( num < 0 ) continue ;
                    f[i - 1][j] = min(f[i - 1][j], val);
                }
                else
                {
                    int val = 0;
                    while ( num > n ) { num -= 2; val += 4; }
                    while ( num >= 0 ) 
                    { 
                        int k = n - max(num, j) + j;
                        if ( k >= 3 && val == 0 ) { R = ans = Mid - 1; goto finish ; }
                        if ( val > 0 && k >= 5 && k >= j + 2 ) break ;
                        f[i - 1][k] = min(f[i - 1][k], val);
                        num -= 2; val += 4;
                    }
                }
            }
            REP(i, 0, 65) if ( f[0][i] == 0 ) { R = ans = Mid - 1; goto finish ; }
            L = Mid + 1;
finish : ;
        }
        printf("%lld\n", ans + 1);        
    }
    return 0;
}
