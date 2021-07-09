/***************************************************************
	File name: complex.cpp
	Author: ljfcnyali
	Create time: 2019年10月29日 星期二 09时46分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, a[maxn], b[maxn], sum[maxn], ans;

inline void Solve(int L, int R)
{
    if ( L > R ) return ; 
    int x = b[R - L + 1], l = L, r = R;
    while ( l <= r ) 
    {
        if ( sum[a[l]] < x ) { r = R; break ; }
        if ( sum[a[r]] < x ) { l = L; break ; }
        ++ l; -- r;
    } 
    if ( l != L && r != R ) { ans = max(ans, R - L + 1); REP(i, L, R) -- sum[a[i]]; return ; }
    if ( r == R && sum[a[l]] < x ) { REP(i, L, l) -- sum[a[i]]; Solve(l + 1, r); }
    else { REP(i, r, R) -- sum[a[i]]; Solve(l, r - 1); }
    if ( r == R && sum[a[l]] < x ) { REP(i, L, l - 1) ++ sum[a[i]]; Solve(L, l - 1); }
    else { REP(i, r + 1, R) ++ sum[a[i]]; Solve(r + 1, R); }
}

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

int main()
{
    freopen("complex.in", "r", stdin);
    freopen("complex.out", "w", stdout);
    read(n);
    REP(i, 1, n) { read(a[i]); ++ sum[a[i]]; }
    REP(i, 1, n) read(b[i]);
    Solve(1, n);
    printf("%d\n", ans);
    return 0;
}
