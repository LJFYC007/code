/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年08月11日 星期二 11时24分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define x first
#define y second
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e18;

int n, q, b[maxn];
pii a[maxn], x;

inline int operator * (pii a, pii b) { return a.x * b.y - a.y * b.x; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    scanf("%lld%lld", &n, &q);
    REP(i, 1, n) scanf("%lld%lld", &a[i].x, &a[i].y);
    while ( q -- ) 
    {
        scanf("%lld%lld", &x.x, &x.y);
        b[0] = INF; REP(i, 1, n) b[i] = x * a[i]; 
        REP(i, 2, n) b[i] += b[i - 1];
        int ans = -INF;
        REP(i, 1, n)
        {
            ans = max(ans, b[i]);
            ans = max(ans, b[i] - b[i - 1]);
            b[i] = min(b[i], b[i - 1]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
