#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int minn(T a, T b) { return a < b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define min minn
#define abs abss

const int maxn = 200010;

int f[maxn], n, m, d[maxn];

struct node
{
    int u, v, w;
} a[maxn];

inline bool cmp(node a, node b)
{
    return a.w > b.w;
}

inline int cha(int x) { return x == f[x] ? x : f[x] = cha(f[x]); }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, m) scanf("%d%d%d", &a[i].u, &a[i].v, &a[i].w);
    REP(i, 1, n) f[i] = i;
    sort ( a + 1, a + m + 1, cmp ) ;
    REP(i, 1, m)
    {
        int fx = cha(a[i].u), fy = cha(a[i].v);
        if ( fx == fy ) { printf("%d\n", a[i].w); return 0; }
        if ( !d[a[i].u] ) d[a[i].u] = a[i].v;         
        else f[cha(d[a[i].u])] = cha(a[i].v);
        if ( !d[a[i].v] ) d[a[i].v] = a[i].u;
        else f[cha(d[a[i].v])] = cha(a[i].u);
    }
    printf("0\n");
    return 0;
}
