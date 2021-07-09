/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年11月03日 星期日 16时12分01秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
#define int long long
typedef long long LL;

const int maxn = 300010;

int n, p[maxn], r[maxn], ans, pre[maxn], suf[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld%lld", &p[i], &r[i]);
    REP(i, 1, n) pre[i] = max(pre[i - 1], p[i] + r[i]);
    suf[n] = p[n] - r[n];
    for ( int i = n - 1; i >= 1; -- i ) suf[i] = min(suf[i + 1], p[i] - r[i]);
    REP(i, 2, n) if ( p[i - 1] < suf[i] ) { puts("-1"); return 0; }
    REP(i, 1, n - 1) if ( pre[i] < p[i + 1] ) { puts("-1"); return 0; }
    ans = (p[n] - p[1]) * 3;
    printf("%lld\n", ans);
    return 0;
}
