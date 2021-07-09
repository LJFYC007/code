/***************************************************************
	File name: point.cpp
	Author: ljfcnyali
	Create time: 2019年09月22日 星期日 10时35分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 500010;

int l[maxn][20], r[maxn][20], n, a[maxn], ans, sum;
map<int, bool> p;

signed main()
{
    freopen("point.in", "r", stdin);
    freopen("point.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) { scanf("%lld", &a[i]); l[i][0] = r[i][0] = a[i]; }
    // REP(i, 1, n) printf("%lld ", a[i]); puts("");
    REP(i, 1, n)
        REP(j, 1, 19)
        {
            if ( i - (1 << (j - 1)) > 0 && l[i - (1 << (j - 1))][j - 1] )
                l[i][j] = __gcd(l[i][j - 1], l[i - (1 << (j - 1))][j - 1]);
        }
    for ( int i = n; i >= 1; -- i )
        REP(j, 1, 19)
        {
            if ( i + (1 << (j - 1)) <= n && r[i + (1 << (j - 1))][j - 1] )
                r[i][j] = __gcd(r[i][j - 1], r[i + (1 << (j - 1))][j - 1]);
        }
    for ( int i = 1; i <= n; ++ i )
    {
        int L = i, R = i;
        for ( int j = 19; j >= 1; -- j )
        {
            if ( l[L][j] && l[L][j] % a[i] == 0 ) L = L - (1 << j) + 1;
            if ( r[R][j] && r[R][j] % a[i] == 0 ) R = R + (1 << j) - 1;
        }
        while ( l[L][1] && l[L][1] % a[i] == 0 ) -- L;
        while ( r[R][1] && r[R][1] % a[i] == 0 ) ++ R;
        if ( R - L > ans ) 
        {
            ans = R - L;
            p.clear(); p[L] = true; sum = 1;
        }
        else if ( R - L == ans ) { if ( !p.count(L) ) p[L] = true, ++ sum; }
    }
    printf("%lld %lld\n", sum, ans);
    int last = 0;
    for ( int i = n; i >= 1; -- i ) if ( p[i] ) { last = i; break ; }
    REP(i, 1, n) if ( p[i] ) printf("%lld%c", i, i == last ? '\n' : ' ');
    return 0;
}
