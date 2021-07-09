/***************************************************************
	File name: G.cpp
	Author: ljfcnyali
	Create time: 2019年10月13日 星期日 18时41分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1000010;

int a[maxn], ans, n, k;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n, k; scanf("%I64d%I64d", &n, &k);
    REP(i, 1, n) { a[i] = i; k -= i; ans += i; }
    if ( k < 0 ) { puts("-1"); return 0; }
    for ( int i = n; i >= 1; -- i )
        if ( k && i > n - i + 1 )
        {
            int x = min(k, i + i - 1 - n);
            swap(a[i], a[i - x]); k -= x; ans += x;
        }
    printf("%I64d\n", ans);
    REP(i, 1, n) printf("%I64d ", i); puts("");
    REP(i, 1, n) printf("%I64d ", a[i]); puts("");
    return 0;
}
