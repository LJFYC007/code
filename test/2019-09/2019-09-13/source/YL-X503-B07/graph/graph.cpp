/***************************************************************
	File name: graph.cpp
	Author: ljfcnyali
	Create time: 2019年09月13日 星期五 08时40分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef unsigned long long LL;

const int maxn = 500010;

struct node
{
    int u, v;
    LL w;
} a[maxn];
int n, m, f[maxn];
LL ans;
bool use[maxn];

inline int cha(int x) { return x == f[x] ? x : f[x] = cha(f[x]); }

inline bool Query(LL x)
{
    REP(i, 1, n) f[i] = i;
    x = 1ll << x;
    REP(i, 1, m)
    {
        if ( !(a[i].w & x) || !use[i] ) continue ;
        int fx = cha(a[i].u), fy = cha(a[i].v);
        if ( fx != fy ) f[fx] = fy;
    }
    int s = cha(1), t = cha(n);
    if ( s != t ) return false;
    REP(i, 1, m)
    {
        if ( !(a[i].w & x) || !use[i] ) { use[i] = false; continue ; }
        int fx = cha(a[i].u), fy = cha(a[i].v);
        if ( fx != s ) use[i] = false;
    }
    // REP(i, 1, m) if ( use[i] ) printf("%d %d %llu\n", a[i].u, a[i].v, a[i].w);
    // printf("%llu\n", x);
    return true;
}

int main()
{
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, m) scanf("%d%d%llu", &a[i].u, &a[i].v, &a[i].w);
    memset(use, true, sizeof(use));
    for ( int i = 63; i >= 0; -- i ) if ( Query(i) ) ans += 1ll << i;
    printf("%llu\n", ans);
    return 0;
}
