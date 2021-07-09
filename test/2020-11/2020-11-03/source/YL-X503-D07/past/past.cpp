/***************************************************************
	File name: past.cpp
	Author: ljfcnyali
	Create time: 2020年11月03日 星期二 09时52分35秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int Mod = 998244353;
const int maxn = 1e5 + 10;

int n;
LL ans;
struct FUCKu
{
    int Begin[maxn], Next[maxn], To[maxn], e, size[maxn], S, Root, RealDep[maxn];
    int anc[maxn], dis[17][maxn], belong[17][maxn], f[maxn], num[17][maxn];
    LL sum[17][maxn];
    bool vis[maxn];
   
    inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

    inline void GetRoot(int u, int fa)
    {
        size[u] = 1; int Max = 0;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa || vis[v] ) continue ;
            GetRoot(v, u); size[u] += size[v];
            Max = max(Max, size[v]);
        }
        Max = max(Max, S - size[u]);
        if ( Max <= S / 2 ) Root = u;
    }

    inline void DFS(int u, int fa, int t, int dep)
    {
        size[u] = 1; belong[dep][u] = t;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa || vis[v] ) continue ;
            dis[dep][v] = dis[dep][u] + 1;
            DFS(v, u, t, dep); size[u] += size[v];
        }
    }

    inline void Solve(int u, int dep)
    {
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( vis[v] ) continue ;
            dis[dep][v] = 1; DFS(v, u, v, dep);
        }
        RealDep[u] = dep; vis[u] = true;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( vis[v] ) continue ;
            S = size[v]; GetRoot(v, u); anc[Root] = u; Solve(Root, dep + 1);
        }
    }

    inline void Modify(int u, int op)
    {
        int x = u, y = RealDep[u];
        while ( x ) 
        {
            sum[y][x] += (op > 0 ? dis[y][u] : -dis[y][u]); num[y][x] += op;
            if ( belong[y][u] ) 
            { 
                sum[y][belong[y][u]] += (op > 0 ? dis[y][u] : - dis[y][u]);
                num[y][belong[y][u]] += op; 
            }
            x = anc[x]; -- y;
        }
    }

    inline int Query(int u)
    {
        LL ret = 0, x = u, y = RealDep[u];
        while ( x ) 
        {
            ret += sum[y][x] - sum[y][belong[y][u]];
            ret += dis[y][u] * (num[y][x] - num[y][belong[y][u]]);
            x = anc[x]; -- y;
        }
        return ret % Mod;
    }
} A, B;

#define For(u) for ( int i = A.Begin[u]; i; i = A.Next[i] )
int dis[maxn], size[maxn], Root, S;
bool vis[maxn];

inline void GetRoot(int u, int fa)
{
    size[u] = 1; int Max = 0;
    For(u)
    {
        int v = A.To[i]; if ( v == fa || vis[v] ) continue ;
        GetRoot(v, u); size[u] += size[v];
        Max = max(Max, size[v]);
    }
    Max = max(Max, S - size[u]);
    if ( Max <= S / 2 ) Root = u;
}

inline void DFS(int u, int fa, int op)
{
    size[u] = 1;
    if ( op == 0 ) B.Modify(u, -1);
    if ( op == 1 ) ans = (ans + 1ll * dis[u] * B.Query(u)) % Mod;
    if ( op == 2 ) B.Modify(u, 1);
    For(u)
    {
        int v = A.To[i]; if ( v == fa || vis[v] ) continue ;
        dis[v] = dis[u] + 1; DFS(v, u, op); size[u] += size[v];
    }
}

inline void Solve(int u)
{
    dis[u] = 0; DFS(u, 0, 2); 
    For(u)
    {
        int v = A.To[i]; if ( vis[v] ) continue ;
        DFS(v, u, 0); DFS(v, u, 1); DFS(v, u, 2);
    }
    DFS(u, 0, 0);
    vis[u] = true;
    For(u)
    {
        int v = A.To[i]; if ( vis[v] ) continue ;
        S = size[v]; GetRoot(v, u); Solve(Root);
    }
}

signed main()
{
    freopen("past.in", "r", stdin);
    freopen("past.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); A.add(u, v); A.add(v, u); }        
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); B.add(u, v); B.add(v, u); }        
    B.S = n; B.GetRoot(1, 0); B.Solve(B.Root, 0);
    S = n; GetRoot(1, 0); Solve(Root);
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
