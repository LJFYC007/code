/***************************************************************
	File name: P2323.cpp
	Author: ljfcnyali
	Create time: 2019年07月09日 星期二 21时44分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 200010;

struct node
{
    int u, v, w1, w2, id;
} a[maxn];

int n, m, f[maxn], k, ans, sum;
bool use[maxn], vis[maxn];

inline int cmp1(node a, node b) { return a.w1 < b.w1 || (a.w1 == b.w1 && a.w2 > b.w2); }

inline int cmp2(node a, node b) { return a.w2 < b.w2; }

inline int cha(int x) { return x == f[x] ? x : f[x] = cha(f[x]); }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &k, &m); -- m;
    REP(i, 1, m) { scanf("%d%d%d%d", &a[i].u, &a[i].v, &a[i].w1, &a[i].w2); a[i].id = i; }
    sort(a + 1, a + m + 1, cmp1);
    REP(i, 1, n) f[i] = i;
    REP(i, 1, m)
    {
        int fx = cha(a[i].u), fy = cha(a[i].v);
        if ( fx != fy ) 
        {
            f[fx] = fy; ans = max(ans, a[i].w1); ++ sum;
            use[a[i].id] = true;
        }
        if ( sum == k ) break ; 
    }
    sort(a + 1, a + m + 1, cmp2);
    REP(i, 1, m)
    {
        if ( use[a[i].id] ) continue ;
        int fx = cha(a[i].u), fy = cha(a[i].v);
        if ( fx != fy ) 
        {
            f[fx] = fy; ans = max(ans, a[i].w2); ++ sum;
            vis[a[i].id] = true;
        }
        if ( sum == n - 1 ) break ;
    }
    printf("%d\n", ans);
    REP(i, 1, m) 
    {
        if ( use[i] ) { printf("%d 1\n", i); continue ; }
        if ( vis[i] ) printf("%d 2\n", i);
    }
    return 0;
}
