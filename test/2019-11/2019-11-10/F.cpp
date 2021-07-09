/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2019年11月10日 星期日 21时55分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 400010;

int n, m, Begin[maxn], Next[maxn], To[maxn], e = 1, sum1, sum2, dfn[maxn], low[maxn], cnt;
bool vis[maxn], flag[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Tarjan(int u)
{
    int son = 0; dfn[u] = low[u] = ++ cnt;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i];
        if ( !dfn[v] ) 
        { 
            Tarjan(v); low[u] = min(low[u], low[v]); 
            if ( low[v] >= dfn[u] && !flag[u] ) { flag[u] = true; ++ sum1; }
        }
        else low[u] = min(low[u], dfn[v]);
        ++ son;
        if ( low[v] > dfn[u] && !vis[i] ) { vis[i] = vis[i ^ 1] = true; ++ sum2; }
    }
    if ( u == 1 && !flag[u] && son >= 2 ) { flag[u] = true; ++ sum1; }
}

int main()
{
    freopen("cut.in", "r", stdin);
    freopen("cut.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    Tarjan(1);
    REP(i, 1, n) if ( flag[i] ) printf("%d ", i); puts("");
    printf("%d %d\n", sum1, sum2);
    return 0;
}
