/***************************************************************
	File name: seat.cpp
	Author: ljfcnyali
	Create time: 2021年01月16日 星期六 10时38分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

unordered_map<int, int> Map;
int n, m, q, a[maxn], t[maxn], ans[maxn], s[100000010];
pii b[maxn];

int main()
{
    freopen("seat.in", "r", stdin);
    freopen("seat.out", "w", stdout);
    scanf("%d%d%d", &m, &n, &q);
    /*
    REP(i, 1, n) { scanf("%d", &t[i]); s[t[i]] = 1; } 
    REP(i, 1, q) { scanf("%d", &b[i].first); b[i].second = i; } 
    sort(b + 1, b + q + 1); int k = 0;
    for ( int i = 1, j; i <= m; i = j + 1 ) 
    {
        j = i - 1; while ( j < m && s[j + 1] == 0 ) ++ j;
        if ( j == i - 1 ) { j = i; continue ; }
        a[++ k] = j - i + 1;
    }
    mem(s); REP(i, 1, k) ++ s[a[i]];
    int now = 1;
    while ( now <= q && b[now].first <= n ) { ans[b[now].second] = t[b[now].first]; ++ now; } 
    for ( int i = m; i >= 1; -- i ) 
    {
        ++ n; 
         
    }
    */
    return 0;
}
