/***************************************************************
	File name: P4383.cpp
	Author: ljfcnyali
	Create time: 2020年05月26日 星期二 19时28分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 6e5 + 10;

int n, k, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], ans, Mid;
pii f[maxn][3];
pii operator + (pii a, pii b) { return pii(a.first + b.first, a.second + b.second); }
pii operator - (pii a, pii b) { return pii(a.first - b.first, a.second - b.second); }
bool operator > (pii a, pii b) 
{ 
    if ( a.first == b.first ) return a.second < b.second;
    return a.first > b.first;
}

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void DFS(int u, int fa)
{
    f[u][0] = f[u][1] = f[u][2] = pii(0, 0);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u);
        f[u][2] = max(f[u][2] + f[v][0], f[u][1] + f[v][1] + pii(W[i] - Mid, 1));
        f[u][1] = max(f[u][1] + f[v][0], f[u][0] + f[v][1] + pii(W[i], 0));
        f[u][0] = f[u][0] + f[v][0];
    }
    f[u][0] = max(f[u][0], max(f[u][1] + pii(-Mid, 1), f[u][2]));
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    // freopen("../../lct9.in", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &k);
    REP(i, 1, n - 1) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); add(v, u, w); }
    int L = -1e9, R = 1e9;
    while ( L <= R ) 
    {
        Mid = (L + R) / 2;
        DFS(1, 0);
        if ( f[1][0].second <= k + 1 ) R = Mid - 1;
        else L = Mid + 1;
    }
    Mid = L; DFS(1, 0);
    if ( f[1][0].second != (k + 1) ) { -- Mid; DFS(1, 0); }
    printf("%lld\n", f[1][0].first + Mid * (k + 1));
    return 0;
}
