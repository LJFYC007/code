/***************************************************************
	File name: P2408.cpp
	Author: ljfcnyali
	Create time: 2019年07月10日 星期三 20时35分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 100010;

LL x[maxn], y[maxn], sa[maxn], height[maxn], n, m, tot, c[maxn], Rank[maxn], ans;
char s[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n); getchar(); m = 128;
    REP(i, 1, n) x[i] = s[i] = getchar();
    REP(i, 1, n) ++ c[x[i]];
    REP(i, 1, m) c[i] += c[i - 1];
    for ( LL i = n; i >= 1; -- i ) sa[c[x[i]] --] = i;
    for ( LL k = 1; k <= n; k <<= 1 ) 
    {
        tot = 0;
        for ( LL i = n; i > n - k; -- i ) y[++ tot] = i;
        REP(i, 1, n) if ( sa[i] > k ) y[++ tot] = sa[i] - k;
        REP(i, 0, m) c[i] = 0;
        REP(i, 1, n) ++ c[x[i]];
        REP(i, 1, m) c[i] += c[i - 1];
        for ( LL i = n; i >= 1; -- i ) sa[c[x[y[i]]] --] = y[i];
        swap(x, y); x[sa[1]] = 1; tot = 1;
        REP(i, 2, n) 
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? tot : ++ tot ;
        if ( tot == n ) break; m = tot;
    }
    REP(i, 1, n) Rank[sa[i]] = i;
    tot = 0; ans = n * (n + 1) / 2;
    REP(i, 1, n)
    {
        if ( Rank[i] == n ) { tot = 0; continue ; }
        LL j = sa[Rank[i] + 1];
        while ( i + tot <= n && j + tot <= n && s[i + tot] == s[j + tot] ) ++ tot;
        height[Rank[i]] = tot; if ( Rank[i] <= n - 1 ) ans -= height[Rank[i]];
        if ( tot ) -- tot;
    }
    printf("%lld\n", ans);
    return 0;
}
