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
typedef long long LL;

const int maxn = 500010;

LL l[maxn][20], r[maxn][20], a[maxn], t[maxn];
int n, ans, p[maxn], tot;

signed main()
{
    freopen("point.in", "r", stdin);
    freopen("point.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%lld", &a[i]); l[i][0] = r[i][0] = a[i]; }
    t[0] = 1; REP(i, 1, 19) t[i] = t[i - 1] << 1;
    // REP(i, 1, n) printf("%lld ", a[i]); puts("");
    REP(i, 1, n)
        REP(j, 1, 19)
        {
            if ( i - t[j - 1] > 0 && l[i - t[j - 1]][j - 1] )
                l[i][j] = __gcd(l[i][j - 1], l[i - t[j - 1]][j - 1]);
        }
    for ( int i = n; i >= 1; -- i )
        REP(j, 1, 19)
        {
            if ( i + t[j - 1] <= n && r[i + t[j - 1]][j - 1] )
                r[i][j] = __gcd(r[i][j - 1], r[i + t[j - 1]][j - 1]);
        }
    for ( int i = 1; i <= n; ++ i )
    {
        int L = i, R = i;
        for ( int j = 19; j >= 1; -- j )
        {
            if ( l[L][j] && l[L][j] % a[i] == 0 ) L = L - t[j] + 1;
            if ( r[R][j] && r[R][j] % a[i] == 0 ) R = R + t[j] - 1;
        }
        while ( l[L][1] && l[L][1] % a[i] == 0 ) -- L;
        while ( r[R][1] && r[R][1] % a[i] == 0 ) ++ R;
        if ( R - L > ans ) 
        {
            ans = R - L;
            tot = 1; p[tot] = L;
        }
        else if ( R - L == ans ) p[++ tot] = L;
        i = R;
    }
    printf("%d %d\n", tot, ans);
    REP(i, 1, tot) printf("%d%c", p[i], i == tot ? '\n' : ' ');
    return 0;
}
