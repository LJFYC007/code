// luogu-judger-enable-o2
/***************************************************************
    File name: P2463.cpp
    Author: ljfcnyali
    Create time: 2019年07月10日 星期三 21时14分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;

int x[maxn], y[maxn], s[maxn], sa[maxn], Rank[maxn], n, m, c[maxn], tot;
int l[maxn], r[maxn], p[maxn], cnt, height[maxn], ans;
int len[1010], a[1010][1010], Stack[maxn], num;
bool vis[maxn];

inline bool Check(int x)
{
    while ( num ) vis[Stack[num --]] = false;
    REP(i, 1, n)
    {
        if ( height[i] < x ) while ( num ) vis[Stack[num --]] = false;
        if ( !vis[p[sa[i]]] ) 
        { 
            vis[p[sa[i]]] = true; 
            Stack[++ num] = p[sa[i]];
            if ( num == cnt ) return true; 
        }
    }
    return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &cnt);
    int L = 0, Min, R, Max = 0;
    R = Min = 2147483647;
    REP(i, 1, cnt)
    {
        scanf("%d", &len[i]);
        REP(j, 1, len[i]) 
        {
            scanf("%d", &a[i][j]);
            if ( j != 1 ) Max = max(Max, a[i][j] - a[i][j - 1]);
        }
        R = min(R, len[i] - 1);
    }
    REP(i, 1, cnt)
    {
        REP(j, 2, len[i])
        {
            x[++ n] = a[i][j] - a[i][j - 1];
            p[n] = i; Min = min(Min, x[n]);
        }
        x[++ n] = ++ Max;
    }
    REP(i, 1, n) { x[i] = x[i] - Min + 1; m = max(m, x[i]); }
    REP(i, 1, n) s[i] = x[i];
    REP(i, 1, n) ++ c[x[i]];
    REP(i, 2, m) c[i] += c[i - 1];
    for ( int i = n; i >= 1; -- i ) sa[c[x[i]] --] = i;
    for ( int k = 1; k <= n; k <<= 1 )
    {
        tot = 0;
        for ( int i = n; i > n - k; -- i ) y[++ tot] = i;
        REP(i, 1, n) if ( sa[i] > k ) y[++ tot] = sa[i] - k;
        REP(i, 0, m) c[i] = 0;
        REP(i, 1, n) ++ c[x[i]];
        REP(i, 2, m) c[i] += c[i - 1];
        for ( int i = n; i >= 1; -- i ) sa[c[x[y[i]]] --] = y[i];
        swap(x, y); x[sa[1]] = 1; tot = 1;
        REP(i, 2, n)
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? tot : ++ tot ;
        if ( tot == n ) break; 
        m = tot;
    }
    REP(i, 1, n) Rank[sa[i]] = i;
    tot = 0;
    REP(i, 1, n)
    {
        if ( Rank[i] == 1 ) continue ; 
        if ( tot ) -- tot;
        int j = sa[Rank[i] - 1];
        while ( i + tot <= n && j + tot <= n && s[i + tot] == s[j + tot] ) ++ tot;
        height[Rank[i]] = tot; 
    }
    while ( L <= R ) 
    {
        int Mid = (L + R) >> 1;
        if ( Check(Mid) ) { ans = Mid; L = Mid + 1; }
        else R = Mid - 1;
    }
    printf("%d\n", ans + 1);
    return 0;
}
