/***************************************************************
	File name: c.cpp
	Author: ljfcnyali
	Create time: 2019年11月13日 星期三 10时09分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 110;

int n, m, a[maxn];

int main()
{
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(o, 1, m)
    {
        int L, R; scanf("%d%d", &L, &R);
        int ans = 0;
        REP(i, L, R) REP(j, i + 1, R) REP(k, j + 1, R) if ( __gcd(a[i], a[j]) == a[k] ) ans += a[k];
        printf("%d\n", ans);
    }
    return 0;
}
