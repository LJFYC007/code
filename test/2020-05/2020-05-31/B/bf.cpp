/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年05月31日 星期日 09时43分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;

int n, m, ans, num[maxn], Begin[maxn * 2], Next[maxn * 2], To[maxn * 2], e;
struct node { int u, v; } Edge[maxn];
bool use[maxn][maxn], vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int x)
{
    if ( vis[x] ) return ; vis[x] = true; ++ num[m];
    for ( int i = Begin[x]; i; i = Next[i] ) 
    {
        int v = To[i]; 
        if ( use[x][v] ) continue ;
        DFS(v);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n - 1) 
    { 
        scanf("%d%d", &Edge[i].u, &Edge[i].v); 
        add(Edge[i].u, Edge[i].v); add(Edge[i].v, Edge[i].u); 
    } 
    REP(i, 1, n - 1) REP(j, i + 1, n - 1) 
    {
        mem(vis);
        use[Edge[i].u][Edge[i].v] = use[Edge[i].v][Edge[i].u] = true;
        use[Edge[j].u][Edge[j].v] = use[Edge[j].v][Edge[j].u] = true;
        // use[Edge[k].u][Edge[k].v] = use[Edge[k].v][Edge[k].u] = true;

        m = 0;
        REP(o, 1, n)        
        {
            if ( vis[o] ) continue ;
            num[++ m] = 0; DFS(o);
        }
        if ( i == 1 && j == 2 )
        {
            REP(o, 1, 3) printf("%d ", num[o]); puts("");
        }
        if ( m == 3 )
        {
            sort(num + 1, num + m + 1);
            if ( num[2] == num[3] ) ans = max(ans, num[3]);
            if ( num[1] == num[3] ) ans = max(ans, num[3]);
            if ( num[1] == num[2] ) ans = max(ans, num[2]);
            // if ( ans == 2 ) { printf("%d %d %d %d\n", Edge[i].u, Edge[i].v, Edge[j].u, Edge[j].v); puts(""); return 0; }
        }

        use[Edge[i].u][Edge[i].v] = use[Edge[i].v][Edge[i].u] = false;
        use[Edge[j].u][Edge[j].v] = use[Edge[j].v][Edge[j].u] = false;
        // use[Edge[k].u][Edge[k].v] = use[Edge[k].v][Edge[k].u] = false;
    }
    printf("%d\n", ans);
    return 0;
}
