/***************************************************************
	File name: kingdom.cpp
	Author: ljfcnyali
	Create time: 2019年11月06日 星期三 09时02分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 400010;
const int INF = 1e18;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, Root[maxn], d[maxn];
int dis[maxn], sum, ret, num[maxn], ans = INF, S, T;
bool use[maxn], vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    ++ num[u]; sum += dis[u];
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || dis[v] ) continue ;
        if ( u == S && v == T ) continue ;
        if ( u == T && v == S ) continue ;
        dis[v] = dis[u] + 1; 
        DFS(v, u); 
        num[u] += num[v];
    }
}

inline void DFS1(int u, int fa)
{
    Root[++ m] = u; vis[u] = true;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || !use[v] || vis[v] ) continue ;
        DFS1(v, u);
    }
}

inline void DFS2(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        if ( u == S && v == T ) continue ;
        if ( u == T && v == S ) continue ;
        num[v] += num[u]; DFS2(v, u);
    }
}

inline void toposort()
{
    queue<int> Q; REP(i, 1, n) if ( d[i] == 1 ) Q.push(i);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); use[u] = false; Q.pop(); 
        for ( int i = Begin[u]; i; i = Next[i] )
        {
            int v = To[i]; -- d[v];
            if ( d[v] == 1 ) Q.push(v);
        }
    }
    int x;
    REP(i, 1, n) if ( use[i] ) { x = i; break ; }
    DFS1(x, 0);
}

signed main()
{
    freopen("kingdom.in", "r", stdin);
    freopen("kingdom.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); ++ d[u]; ++ d[v]; }
    memset(use, true, sizeof(use));
    toposort();    
    REP(i, 1, m)
    {
        S = Root[i]; T = i == m ? Root[1] : Root[i + 1];
        REP(j, 1, n) num[j] = dis[j] = 0; sum = 0;
        dis[1] = 1; DFS(1, 0); DFS2(1, 0);
        ret = n * sum;
        REP(j, 1, n) ret -= num[j];
        printf("%d %d %d\n", S, T, ret);
        ans = min(ans, ret);
    }
    printf("%lld\n", ans);
    return 0;
}

