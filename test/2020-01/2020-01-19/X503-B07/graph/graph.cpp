/***************************************************************
	File name: graph.cpp
	Author: ljfcnyali
	Create time: 2020年01月19日 星期日 10时55分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 4e5 + 10;

int n, q, A, B, m, f[maxn];
struct node { int u, v, w; } a[maxn], b[maxn], Edge[maxn];

inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

namespace Subtask1
{
    inline int main()
    {
        REP(i, 1, A) Edge[i] = a[i];
        int ans = 0; m = A;
        REP(i, 1, n) f[i] = i;
        sort(Edge + 1, Edge + m + 1, [](node &a, node &b) { return a.w < b.w; });
        REP(i, 1, m)
        {
            int fx = find(Edge[i].u), fy = find(Edge[i].v);
            if ( fx != fy ) { f[fx] = fy; ans += Edge[i].w; }
        }
        while ( q -- ) 
        {
            int x; scanf("%lld", &x);
            printf("%lld\n", ans + x * (n - 1));
        }
        return 0;
    }
}

signed main()
{
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);
    scanf("%lld%lld%lld%lld", &n, &A, &B, &q);
    REP(i, 1, A) scanf("%lld%lld%lld", &a[i].u, &a[i].v, &a[i].w);
    REP(i, 1, B) scanf("%lld%lld%lld", &b[i].u, &b[i].v, &b[i].w);
    if ( q > 1000 ) return Subtask1 :: main();
    while ( q -- ) 
    {
        int x, ans = 0; scanf("%lld", &x);
        REP(i, 1, A) { Edge[i] = a[i]; Edge[i].w += x; }
        REP(i, 1, B) { Edge[i + A] = b[i]; Edge[i + A].w -= x; }
        m = A + B;
        REP(i, 1, n) f[i] = i;
        sort(Edge + 1, Edge + m + 1, [](node &a, node &b) { return a.w < b.w; });
        REP(i, 1, m)
        {
            int fx = find(Edge[i].u), fy = find(Edge[i].v);
            if ( fx != fy ) { f[fx] = fy; ans += Edge[i].w; }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
