/***************************************************************
	File name: AGC023D.cpp
	Author: ljfcnyali
	Create time: 2021年01月14日 星期四 14时36分51秒
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

int n, s, a[maxn], b[maxn], ans;

inline int Solve(int l, int r, int x)
{
    if ( x < a[l] ) { ans += a[r] - x; return a[r]; }
    if ( x > a[r] ) { ans += x - a[l]; return a[l]; } 
    if ( b[l] >= b[r] ) { b[l] += b[r]; ans += a[r] - Solve(l, r - 1, x); return a[r]; }
    else { b[r] += b[l]; ans += Solve(l + 1, r, x) - a[l]; return a[l]; }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &s);
    REP(i, 1, n) scanf("%lld%lld", &a[i], &b[i]);
    Solve(1, n, s);
    printf("%lld\n", ans);
    return 0;
}
