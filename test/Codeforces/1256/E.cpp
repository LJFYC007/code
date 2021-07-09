/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年11月04日 星期一 21时47分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 200010;
const int Min = 1e9 + 10;

int n, f[maxn], g[maxn], ans[maxn];
pii a[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) { int x; scanf("%d", &x); a[i] = pii(x, i); }
    sort(a + 1, a + n + 1);
    f[3] = a[3].first - a[1].first;
    int Min = -a[1].first, pos = 0;
    REP(i, 2, n)
    {
        if ( i > 5 && f[i - 3] - a[i - 2].first <= Min ) { Min = f[i - 3] - a[i - 2].first; pos = i - 3; }
        f[i] = Min + a[i].first; g[i] = pos;
    }
    int now = n, tot = 0;
    while ( now ) 
    {
        int x = g[now] + 1;
        ++ tot;
        REP(i, x, now) ans[a[i].second] = tot;
        now = g[now];
    }
    printf("%d %d\n", f[n], tot);
    REP(i, 1, n) printf("%d ", ans[i]); puts("");
    return 0;
}
