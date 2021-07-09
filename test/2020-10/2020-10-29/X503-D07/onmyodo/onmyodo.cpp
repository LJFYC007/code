/***************************************************************
	File name: onmyodo.cpp
	Author: ljfcnyali
	Create time: 2020年10月29日 星期四 11时09分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, k, val[maxn], sum, ans, a[maxn * 10];

inline void read(int &x)
{
    x = 0; char c = getchar();
    while ( (c < '0' || c > '9') && c != '-' ) c = getchar();
    bool flag = false;
    if ( c == '-' ) { flag = true; c = getchar(); }
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
    if ( flag ) x = -x;
}

signed main()
{
    freopen("onmyodo.in", "r", stdin);
    freopen("onmyodo.out", "w", stdout);
    read(n);
    REP(i, 1, n)
    {
        read(k); REP(j, 1, k) { read(a[j]); sum += a[j]; }
        REP(j, 1, k / 2) ans += a[j];
        if ( k % 2 == 1 ) val[++ m] = a[(k + 1) / 2];
    }
    sort(val + 1, val + m + 1);
    int op = 0;
    for ( int i = m; i >= 1; -- i ) 
    {
        if ( !op ) ans += val[i];
        op ^= 1;
    }
    printf("%lld %lld\n", ans, sum - ans);
    return 0;
}
