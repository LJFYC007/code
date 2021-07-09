/***************************************************************
	File name: interval.cpp
	Author: ljfcnyali
	Create time: 2020年10月07日 星期三 14时45分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5e5 + 10;

int n, a[maxn], f[maxn][20], ans = -1, sum, len[maxn];

int main()
{
    freopen("interval.in", "r", stdin);
    freopen("interval.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%d", &a[i]); f[i][0] = a[i]; }
    REP(j, 1, 18) REP(i, 1, n - (1 << j - 1)) 
        f[i][j] = __gcd(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
    REP(i, 1, n)
    {
        int l = i, r = i;
        for ( int j = 18; j >= 0; -- j ) 
        {
            if ( r + (1 << j) <= n && __gcd(f[r + 1][j], a[i]) == a[i] ) r += (1 << j);
            if ( l - (1 << j) >= 1 && __gcd(f[l - (1 << j)][j], a[i]) == a[i] ) l -= (1 << j);
        }
        len[l] = max(len[l], r - l); ans = max(ans, r - l);
    }
    REP(i, 1, n) if ( len[i] == ans ) ++ sum;
    printf("%d %d\n", sum, ans);
    REP(i, 1, n) if ( len[i] == ans ) printf("%d ", i); puts("");
    return 0;
}
