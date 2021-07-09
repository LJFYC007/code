/***************************************************************
	File name: number.cpp
	Author: ljfcnyali
	Create time: 2020年11月18日 星期三 08时51分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, a[maxn], b[maxn], ans;

int main()
{
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) { int x; scanf("%d", &x); ++ a[x]; }
    REP(i, 1, n) { int x; scanf("%d", &x); ++ b[x]; }
    REP(i, 0, n - 1) REP(j, 0, n - 1)
        if ( i * j % n == m ) 
            ans += a[i] * b[j];
    printf("%d\n", ans);
    return 0;
}
