/***************************************************************
	File name: score.cpp
	Author: ljfcnyali
	Create time: 2020年10月07日 星期三 15时56分03秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, w[maxn], ans;
vector<int> a[maxn], b[maxn];
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa, int ret)
{
    for ( auto i : a[u] ) vis[i] = true;
    for ( auto i : b[u] ) if ( vis[i] ) ret += w[i];
    ans = max(ans, ret);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u, ret);
    }
    for ( auto i : a[u] ) vis[i] = false;
}

int main()
{
    freopen("score.in", "r", stdin);
    freopen("score1.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    REP(i, 1, m)
    {
        int x, y; scanf("%d%d%d", &x, &y, &w[i]);
        a[x].push_back(i); b[y].push_back(i);
    }
    REP(i, 1, n) DFS(i, 0, 0);
    printf("%d\n", ans);
    return 0;
}
