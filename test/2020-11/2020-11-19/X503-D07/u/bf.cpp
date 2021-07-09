/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年11月19日 星期四 08时35分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e3 + 10;

int n, q, a[maxn][maxn];

signed main()
{
    freopen("u.in", "r", stdin);
    freopen("u1.out", "w", stdout);
    scanf("%lld%lld", &n, &q);
    REP(i, 1, q)
    {
        int r, c, l, s; scanf("%lld%lld%lld%lld", &r, &c, &l, &s);
        REP(x, r, r + l - 1) REP(y, c, x - r + c)
        {
            if ( x > n || y > n ) continue ;
            a[x][y] += s;
        }
    }
    int ans = 0;
    REP(i, 1, n) REP(j, 1, n) ans ^= a[i][j];
    // REP(i, 1, n) { REP(j, 1, n) printf("%lld ", a[i][j]); puts(""); }
    printf("%lld\n", ans);
    return 0;
}
