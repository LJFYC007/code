/***************************************************************
	File name: lost.cpp
	Author: ljfcnyali
	Create time: 2020年10月03日 星期六 09时21分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 5e5 + 10;

int n, c[maxn], Begin[maxn], Next[maxn], To[maxn], e, dis[maxn];
double ans[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; dis[v] = dis[u] + 1;
        DFS(v);
    }
}

signed main()
{
    freopen("lost.in", "r", stdin);
    freopen("lost.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &c[i]);
    REP(i, 2, n) { int x; scanf("%d", &x); add(x, i); }
    dis[1] = 1; DFS(1);
    REP(i, 2, n) printf("%.7lf\n", ans[i]);
    return 0;
}
