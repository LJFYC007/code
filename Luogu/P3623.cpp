/***************************************************************
	File name: P3623.cpp
	Author: ljfcnyali
	Create time: 2019年06月25日 星期二 11时11分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 200010;

struct node
{
    int u, v, w, opt;
} a[maxn];

int n, m, k, f[maxn], sum, tot, s;
bool vis[maxn];

inline int cmp(node a, node b)
{
    return a.w < b.w || (a.w == b.w && a.opt > b.opt); 
}

inline int cha(int x) { return x == f[x] ? x : f[x] = cha(f[x]); }

inline bool check(int x)
{
    REP(i, 1, m) if ( a[i].opt == 0 ) a[i].w += x;
    sort(a + 1, a + m + 1, cmp);
    REP(i, 1, n) f[i] = i;
    tot = s = 0;
    mem(vis);
    REP(i, 1, m)
    {
        int fx = cha(a[i].u), fy = cha(a[i].v);
        if ( fx != fy ) 
        {
            f[fx] = fy;
            ++ s; 
            if ( a[i].opt == 0 ) ++ tot;
            vis[i] = true;
        }
        if ( s == n - 1 ) break ;
    }
    REP(i, 1, m) if ( a[i].opt == 0 ) a[i].w -= x;
    if ( tot == k )
    {
        REP(i, 1, m) if ( vis[i] == true ) printf("%d %d %d\n", a[i].u, a[i].v, a[i].opt);
        exit(0);
    }
    if ( tot > k ) return true;
    return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    srand(time(0));
    scanf("%d%d%d", &n, &m, &k);
    REP(i, 1, m) { scanf("%d%d%d", &a[i].u, &a[i].v, &a[i].opt); a[i].w = rand() % 100; }
    int l = -150, r = 150;
    while ( l <= r ) 
    {
        int Mid = l + r >> 1;
        if ( check(Mid) ) l = Mid + 1;
        else r = Mid - 1;
    }
    printf("no solution\n");
    return 0;
}
