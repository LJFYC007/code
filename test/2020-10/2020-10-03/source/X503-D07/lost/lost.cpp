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
typedef long long LL;

const int maxn = 5e5 + 10;

int n, c[maxn], Begin[maxn], Next[maxn], To[maxn], e, dis[maxn], anc[maxn][20];
pii a[maxn];
double ans[maxn];

inline double find(pii a, pii b) { return (b.x - a.x) * 1.0 / (a.y - b.y); }

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u)
{
    REP(j, 1, 18) anc[u][j] = anc[anc[u][j - 1]][j - 1];
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; dis[v] = dis[u] + 1; a[v] = pii(c[v], dis[v]);
        int pos = u;
        for ( int j = 18; j >= 0; -- j ) 
        {
            int x = anc[pos][j]; if ( !anc[x][0] ) continue ;
            if ( find(a[x], a[anc[x][0]]) < find(a[v], a[x]) ) pos = x;
        }
        if ( anc[pos][0] && find(a[pos], a[anc[pos][0]]) < find(a[v], a[pos]) ) pos = anc[pos][0];
        ans[v] = find(a[v], a[pos]);
        anc[v][0] = pos; DFS(v);
    }
}

signed main()
{
    freopen("lost.in", "r", stdin);
    freopen("lost.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &c[i]);
    REP(i, 2, n) { int x; scanf("%d", &x); add(x, i); }
    dis[1] = 1; a[1] = pii(c[1], 1); DFS(1);
    REP(i, 2, n) printf("%.7lf\n", ans[i]);
    return 0;
} 
