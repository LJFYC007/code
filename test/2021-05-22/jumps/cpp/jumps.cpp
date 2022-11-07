#include "jumps.h"
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 0x3f3f3f3f;

int n, st[maxn][21], lg[maxn], anc[4][maxn][21], dis[maxn], Max[maxn][21];
vector<int> h; pii a[maxn], b[maxn];

inline int get(int l, int r)
{
    int x = lg[r - l + 1];
    return h[st[l][x]] > h[st[r - (1 << x) + 1][x]] ? st[l][x] : st[r - (1 << x) + 1][x];
}

inline int find(int x, int y)
{
    int ret = y;
    for ( int i = 20; i >= 0; -- i ) 
        if ( dis[anc[3][x][i]] >= dis[y] ) 
        {
            ret = max(ret, Max[x][i]);
            x = anc[3][x][i];
        }
    return ret;
}

inline bool check(int x, int y, int l, int r) 
{ 
    if ( y < a[x].first || y > a[x].second ) return true;
    return find(y, x) < l;
}

inline int query(int x, int l, int r)
{
    l = max(a[x].second + 1, l); if ( l > r ) return INF;
    int ret = 0, pos = get(l, r);
    for ( int i = 20; i >= 0; -- i ) 
    {
        int y = anc[2][x][i];
        if ( dis[y] >= dis[pos] && check(b[y].first, x, l, r) && check(b[y].second, x, l, r) ) { x = y; ret += (1 << i); }
    }
    if ( dis[x] >= dis[pos] && l <= x && x <= r ) return ret;
    int y = anc[2][x][0];
    if ( dis[y] >= dis[pos] && l <= y && y <= r ) return ret + 1;

    for ( int o = 1; o >= 0; -- o ) for ( int i = 20; i >= 0; -- i ) 
    {
        int y = anc[o][x][i];
        if ( dis[y] >= dis[pos] && check(b[y].first, x, l, r) && check(b[y].second, x, l, r) ) { x = y; ret += (1 << i); }
    }
    if ( dis[x] >= dis[pos] && l <= x && x <= r ) return ret;
    return INF;
}

inline void Build(int l, int r, int x, int y, int dep, int fa)
{
    if ( l > r ) return ;
    int pos = get(l, r); dis[pos] = dep; a[pos] = pii(l, r);
    anc[0][pos][0] = x; anc[1][pos][0] = y; anc[3][pos][0] = fa; Max[pos][0] = pos;
    anc[2][pos][0] = (!x || !y) ? x + y : (dis[x] < dis[y] ? x : y); 
    if ( fa == y ) b[fa].first = pos; else b[fa].second = pos;
    Build(l, pos - 1, x, pos, dep + 1, pos); Build(pos + 1, r, pos, y, dep + 1, pos);
}

void init(int N, vector<int> H) 
{
    n = N; h.resize(n + 1); REP(i, 1, n) h[i] = H[i - 1];
    REP(i, 1, n) st[i][0] = i; 
    REP(i, 2, n) lg[i] = lg[i >> 1] + 1;
    REP(j, 1, 20) REP(i, 1, n) if ( i + (1 << j - 1) <= n )
        st[i][j] = h[st[i][j - 1]] > h[st[i + (1 << j - 1)][j - 1]] ? st[i][j - 1] : st[i + (1 << j - 1)][j - 1];
    Build(1, n, 0, 0, 1, 0);    
    REP(o, 0, 3) REP(j, 1, 20) REP(i, 1, n) anc[o][i][j] = anc[o][anc[o][i][j - 1]][j - 1];
    REP(j, 1, 20) REP(i, 1, n) Max[i][j] = max(Max[i][j - 1], Max[anc[3][i][j - 1]][j - 1]);
}

int minimum_jumps(int A, int B, int C, int D) 
{
    ++ A; ++ B; ++ C; ++ D;
    int ans = INF, pos = get(A, B);
    ans = query(pos, C, D);

    int L = max(C, a[pos].first), R = min(D, a[pos].second);
    if ( L <= R ) 
    {
        int x = get(L, R), l = max(A, a[x].first), r = min(B, a[x].second);
        if ( l <= r ) ans = min(ans, query(get(l, r), L, R));
    }
    return ans == INF ? -1 : ans;
}
