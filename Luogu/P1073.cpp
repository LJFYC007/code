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

const int maxn = 1000010;

int Begin[maxn], Next[maxn], To[maxn], e, a[maxn], n, m;
int f[maxn], mi[maxn];

inline void add(int u, int v)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline void DFS(int u, int Min, int fa)
{
    Min = min(Min, a[u]);
    bool flag = false;
    if ( mi[u] > Min ) { mi[u] = Min; flag = true; }
    int Max = max(f[fa], a[u] - Min);
    if ( Max > f[u] ) { f[u] = Max; flag = true; }
    if ( flag == false ) return ;
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i];
        DFS(v, Min, u);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, m)
    {
        int u, v, x; scanf("%d%d%d", &u, &v, &x);
        add(u, v);
        if ( x == 2 ) add(v, u);
    }
    REP(i, 0, n) mi[i] = 0x3f3f3f3f;
    DFS(1, 0x3f3f3f3f, 0);
    // REP(i, 1, n) printf("%d ", f[i]);
    printf("%d\n", f[n]);
    return 0;
}
