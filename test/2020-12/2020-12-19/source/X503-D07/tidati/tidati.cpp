/***************************************************************
	File name: tidati.cpp
	Author: ljfcnyali
	Create time: 2020年12月19日 星期六 10时22分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, k, val, a[maxn], b[maxn], ans[maxn];
bool flag;

inline void add(int x) { ++ m; ans[m - 1] = x; a[m] = a[m - 1] + a[x]; }

signed main()
{
    scanf("%lld", &k); val = k;
    while ( k ) { b[++ n] = k % 2; k /= 2; } 
    if ( b[n - 1] == 0 ) 
    { 
        -- n; int pos = n;
        while ( b[pos] == 0 ) { b[pos] = 1; -- pos; }
    }

    a[1] = m = 1; REP(i, 1, n - 2) add(i);
    REP(i, 1, n - 3) if ( b[i] == 1 && b[i + 1] == 1 ) { add(i); ++ i; }
    int x = m; add(x); add(x); x = val - a[m];
    for ( int i = n - 1; i >= 1; -- i ) while ( x >= (1 << i - 1) ) { x -= (1 << i - 1); add(i); }

    printf("%lld\n", m);
    REP(i, 1, m - 1) printf("%lld ", ans[i]); puts("");
    return 0;
}
