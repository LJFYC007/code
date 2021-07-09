/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年07月23日 星期四 09时38分08秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e18;

int T, n, k, a[maxn], pre[maxn], suf[maxn];

inline void Solve(int l, int r)
{
    if ( l == 1 && r == n ) { puts("Yes"); return ; }
    int pos = -1; bool flag = false;
    for ( int i = l - 1; i >= 1; -- i ) 
    {
        if ( a[i] < a[r] ) break ; 
        if ( a[i] > a[l] ) { pos = i; break ; }
    }
    if ( pos != -1 ) { l = pos; flag = true; }
    pos = -1;
    REP(i, r + 1, n) 
    {
        if ( a[i] > a[l] ) break ; 
        if ( a[i] < a[r] ) { pos = i; break ; }
    }
    if ( pos != -1 ) { r = pos; flag = true; }
    if ( flag ) { Solve(l, r); return ; }

    while ( l != 1 || r != n ) 
    {
        while ( l > 1 && a[l - 1] >= a[l] ) -- l;
        while ( r < n && a[r + 1] <= a[r] ) ++ r;
        if ( l == 1 && r == n ) break ;
        if ( pre[l] > suf[r] ) 
        {
            if ( l > 1 && a[l - 1] >= a[r] ) -- l;
            else if ( r < n && a[r + 1] <= a[l] ) ++ r;
            else { puts("No"); return ; }
        }
        else
        {
            if ( r < n && a[r + 1] <= a[l] ) ++ r;
            else if ( l > 1 && a[l - 1] >= a[r] ) -- l;
            else { puts("No"); return ; }
        }
    }
    puts("Yes");
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld", &n, &k);
        REP(i, 1, n) scanf("%lld", &a[i]);
        REP(i, 2, n) a[i] += a[i - 1];
        pre[0] = suf[n + 1] = -INF;
        REP(i, 1, n) pre[i] = max(pre[i - 1], a[i]);
        for ( int i = n; i >= 1; -- i ) suf[i] = max(suf[i + 1], a[i]);
        Solve(k, k);
    }
    return 0;
}
