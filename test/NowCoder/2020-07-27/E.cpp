/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2020年07月27日 星期一 12时37分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, k, a[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &k);
    int sum = n * (n + 1) / 2;
    if ( sum % n != k ) { puts("-1"); return 0; }
    a[n] = n;
    int l = 1, r = n - 1, now = 1;
    if ( n % 2 == 0 ) { a[n - 1] = n / 2; -- r; }
    while ( l <= r ) 
    {
        if ( l + 2 <= r + 1 ) { a[l] = now; a[l + 1] = n - now; ++ now; l += 2; }
        if ( l + 2 <= r + 1 ) { a[r] = now; a[r - 1] = n - now; ++ now; r -= 2; }
        if ( l == r ) break ;
    }
    REP(i, 1, n) printf("%d ", a[i]); puts("");
    return 0;
}
