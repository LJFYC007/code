#include "paint.h"
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 0x3f3f3f3f;

int n, m, k, f[maxn], g[20010][2010], Min[maxn << 2];
vector<int> col[maxn], c;
bool vis[maxn];

inline void Modify(int root, int l, int r, int pos, int val)
{
    if ( l == r ) { Min[root] = val; return ; }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
    else Modify(rson, Mid + 1, r, pos, val);
    Min[root] = min(Min[lson], Min[rson]);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Min[root];
    int Mid = l + r >> 1, ret = INF;
    if ( L <= Mid ) ret = min(ret, Query(lson, l, Mid, L, R));
    if ( Mid < R ) ret = min(ret, Query(rson, Mid + 1, r, L, R));
    return ret;
}

inline int Solve(int pos)
{
    if ( pos == n ) return 0;
    if ( pos > n - m ) return -1;
    if ( f[pos] >= -1 ) return f[pos];
    int ret = INF;
    REP(i, 0, m - 1) if ( g[pos][i] == m ) 
    {
        REP(j, 1, m) { int num = Solve(pos + j); if ( num != -1 ) ret = min(ret, num + 1); }
        break ; 
    }
    if ( ret == INF ) ret = -1; f[pos] = ret; return ret;
}

int minimumInstructions(int N, int M, int K, vector<int> C, vector<int> a, vector<vector<int>> b) 
{
    n = N; m = M; k = K; c = C;
    REP(i, 0, m - 1) REP(j, 0, a[i] - 1) col[b[i][j]].push_back(i);
    for ( int i = n - 1; i >= 0; -- i )
        for ( auto j : col[c[i]] )
        {
            g[i][j] = min(g[i + 1][(j + 1) % m], m - 1) + 1;
            if ( g[i][j] == m ) vis[i] = true;
        }
    Modify(1, 0, n, n, 0);
    REP(i, n - m + 1, n - 1) Modify(1, 0, n, i, INF);
    for ( int i = n - m; i >= 0; -- i ) 
    {
        if ( !vis[i] ) { Modify(1, 0, n, i, INF); continue ; }
        int x = Query(1, 0, n, i + 1, i + m);
        if ( x != INF ) Modify(1, 0, n, i, x + 1);
        else Modify(1, 0, n, i, INF);
    }
    return Query(1, 0, n, 0, 0) == INF ? -1 : Query(1, 0, n, 0, 0);
}
