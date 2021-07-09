/***************************************************************
	File name: P2619.cpp
	Author: ljfcnyali
	Create time: 2019年06月25日 星期二 10时01分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;

struct node
{
    int u, v, w, color;
} a[maxn];

int n, m, k, f[maxn], ans, sum, tot, s;

inline int cha(int x) { return x == f[x] ? x : f[x] = cha(f[x]); }

inline int cmp(node a, node b) { return a.w < b.w || (a.w == b.w && a.color < b.color); }

inline bool check(int x)
{
    REP(i, 1, m) if ( a[i].color == 0 ) a[i].w += x;
    sort(a + 1, a + m + 1, cmp);
    REP(i, 1, n) f[i] = i;
    sum = tot = s = 0;
    REP(i, 1, m)
    {
        int fx = cha(a[i].u), fy = cha(a[i].v);
        if ( fx != fy ) 
        {
            f[fx] = fy;
            sum += a[i].w;
            ++ s;
            if ( a[i].color == 0 ) ++ tot;
        }
        if ( s == n - 1 ) break ;
    }
    REP(i, 1, m) if ( a[i].color == 0 ) a[i].w -= x;
    if ( tot < k ) return false;
    return true;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &k);
    REP(i, 1, m) 
    {
        scanf("%d%d%d%d", &a[i].u, &a[i].v, &a[i].w, &a[i].color);
        ++ a[i].u; ++ a[i].v;
    }
    int l = -100, r = 100;
    while ( l <= r ) 
    {
        int Mid = l + r >> 1;
        if ( check(Mid) ) 
        {
            ans = sum - Mid * k;
            l = Mid + 1;
        }
        else r = Mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}
