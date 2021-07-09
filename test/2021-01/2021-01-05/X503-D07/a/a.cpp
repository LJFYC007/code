/***************************************************************
	File name: a.cpp
	Author: ljfcnyali
	Create time: 2021年01月05日 星期二 09时01分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, g, ans;

int main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) { int x; scanf("%d", &x); g = __gcd(x, g); }
    scanf("%d", &m);
    REP(i, 1, m) { int x; scanf("%d", &x); if ( x % g == 0 ) ++ ans; }
    printf("%d\n", ans);
    return 0;
}
