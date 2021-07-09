/***************************************************************
	File name: plan.cpp
	Author: ljfcnyali
	Create time: 2020年11月03日 星期二 09时33分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
#define int long long

const int maxn = 1e5 + 10;
const int INF = 1e18;

int n, L, R, a[maxn], ans;
int l[maxn], r[maxn], f[maxn];

inline void DFS(int i, int sum)
{
    if ( sum < 0 ) { puts("-1"); exit(0); }
    f[i] = sum + a[i]; ans += sum; if ( i == n ) return ;
    DFS(i + 1, max(L - a[i + 1] - a[i] - sum, l[i + 1]));
}

signed main()
{
    freopen("plan.in", "r", stdin);
    freopen("plan.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &L, &R);
    REP(i, 1, n) scanf("%lld", &a[i]);
    l[n] = 0; r[n] = R - a[n];
    for ( int i = n - 1; i >= 1; -- i )
    {
        l[i] = max(0ll, L - a[i] - a[i + 1] - r[i + 1]);
        r[i] = R - a[i] - a[i + 1] - l[i + 1];
        if ( l[i] > r[i] ) { puts("-1"); return 0; }
    }
    DFS(1, l[1]);
    printf("%lld\n", ans);
    REP(i, 1, n) printf("%lld ", f[i]); puts("");
    return 0;
}
