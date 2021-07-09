/***************************************************************
	File name: LibreOJ_566.cpp
	Author: ljfcnyali
	Create time: 2020年05月27日 星期三 09时50分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, p[maxn], f[maxn], ans, sum, Mid, N;
struct node 
{ 
    int u, v, w, col; 
    bool operator < (const node &a) const { return w > a.w; } 
} a[maxn], Edge[maxn];

inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

inline void Kruscal()
{
    REP(i, 1, n) f[i] = i;
    int L = 1, R = m;
    REP(i, 1, m)
    {
        node x;
        if ( a[L].w >= Mid - a[R].w ) { x = a[L]; ++ L; x.col = 0; }
        else { x = a[R]; x.w = Mid - a[R].w; -- R; x.col = 1; }
        int fx = find(x.u), fy = find(x.v);
        if ( fx != fy ) 
        { 
            f[fx] = fy; 
            ans += x.w;
            sum += x.col;
        }
    }
    ans -= Mid * N;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m); N = (n - 1) / 2;
    REP(i, 1, m) scanf("%lld%lld%lld", &a[i].u, &a[i].v, &a[i].w);
    sort(a + 1, a + m + 1);
    int L = 0, R = a[1].w * 2 + 1, ret = 0;
    while ( L <= R ) 
    {
        Mid = (L + R) >> 1;
        sum = ans = 0; Kruscal();
        if ( sum == N ) { printf("%lld\n", ans); return 0; }
        if ( sum < N ) { L = Mid + 1; ret = ans; }
        else R = Mid - 1;
    }
    printf("%lld\n", ret);
    return 0;
}
