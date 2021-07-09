/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2019年10月31日 星期四 16时35分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define int long long
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 500010;

int p[maxn], q[maxn], n, k, a[maxn], b[maxn];
set<int> Set;

inline void print()
{
    puts("Yes");
    REP(i, 1, n) printf("%lld ", a[i]); puts("");
    REP(i, 1, n) printf("%lld ", b[i]); puts("");
    exit(0);
}

signed main()
{
    freopen("array.in", "r", stdin);
    freopen("array.out", "w", stdout);
    scanf("%lld%lld", &n, &k);
    REP(i, 1, n) scanf("%lld", &p[i]);
    REP(i, 1, n) { scanf("%lld", &q[i]); b[q[i]] = -n + i - 1; a[i] = n; }
    REP(i, 1, n)
    {
        if ( k == 0 ) print();
        if ( n - p[i] <= k ) { a[p[i]] = 0; k -= n - p[i]; continue ; }
        REP(j, p[i] + 1, n) Set.insert(b[j]);
        while ( k + 1 < Set.size() ) Set.erase((-- Set.end()));
        a[p[i]] = -*(-- Set.end());
        print();
    }
    puts("No");
    return 0;
}
