/***************************************************************
	File name: P4382.cpp
	Author: ljfcnyali
	Create time: 2020年05月27日 星期三 17时04分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e3 + 10;
// const int maxm = 1e5 + 10;
const int INF = 0x3f3f3f3f;

int n, m, b[maxn], s[maxn], ans1[maxn], ans2[maxn], g[maxn];
vector<int> a[maxn][maxn];
struct node { int v, w, id; node(int a = 0, int b = 0, int c = 0) { v = a; w = b; id = c; } } ;
struct Dinic
{
    int dis[maxn];
    vector<node> Edge[maxn];

    inline void add(int u, int v, int w)
    {
        // cerr << u << " " << v << " " << w << endl;
        Edge[u].push_back(node(v, w, Edge[v].size()));
        Edge[v].push_back(node(u, 0, Edge[u].size() - 1));
    }

    inline void Delete(int u, int v) { Edge[u].pop_back(); Edge[v].pop_back(); }

    inline bool BFS(int s, int t)
    {
        REP(i, 1, t) dis[i] = 0; dis[s] = 1;
        queue<int> Q; Q.push(s);
        while ( !Q.empty() ) 
        {
            int u = Q.front(); Q.pop();
            for ( auto i : Edge[u] ) 
            {
                int v = i.v; if ( dis[v] || !i.w ) continue ;
                dis[v] = dis[u] + 1; Q.push(v);
                if ( v == t ) return true;
            }
        }
        return false;
    }

    inline int DFS(int u, int t, int flow)
    {
        if ( u == t || !flow ) return flow;  
        for ( auto &i : Edge[u] ) 
        {
            int v = i.v; if ( dis[v] != dis[u] + 1 || !i.w ) continue ;
            int x = DFS(v, t, min(flow, i.w));
            if ( !x ) continue ;
            i.w -= x; Edge[v][i.id].w += x;
            return x;
        }
        dis[u] = 0; return 0;
    }
    
    inline int Solve(int s, int t)
    {
        while ( BFS(s, t) ) 
        { 
            int x = DFS(s, t, INF); 
            if ( x ) return x; 
        }
        return 0;
    }

    inline void print()
    {
        REP(u, 1, n + m + 2) 
            for ( auto i : Edge[u] ) 
                printf("%lld %lld %lld %lld\n", u, i.v, i.w, i.id);
    }
} A, f[210];

inline bool Check(int t, int x)
{
    A = f[t];
    REP(i, 1, s[x]) for ( auto j : a[x][i] ) A.add(x, n + j, 1);
    int ret = A.Solve(n + m + 1, n + m + 2);
    return ret > 0;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T, C;
    scanf("%lld%lld", &T, &C);
    while ( T -- ) 
    {
        mem(a); mem(A.Edge); 
        scanf("%lld%lld", &n, &m);
        REP(i, 1, m) scanf("%lld", &b[i]);
        REP(i, 1, n) REP(j, 1, m) { int x; scanf("%lld", &x); a[i][x].push_back(j); }
        REP(i, 1, n) scanf("%lld", &s[i]);

        int S = n + m + 1, T = n + m + 2;
        REP(i, 1, n) A.add(S, i, 1);
        REP(i, 1, m) A.add(n + i, T, b[i]);

        REP(i, 1, n)
        {
            f[i] = A; 
            REP(j, 1, m) 
            {
                if ( !a[i][j].size() ) continue ;
                for ( auto k : a[i][j] ) A.add(i, n + k, 1);
                int x = A.Solve(S, T);
                if ( x > 0 ) { g[i] = g[i - 1] + x; ans1[i] = j; goto Next ; }
                for ( int k = a[i][j].size() - 1; k >= 0; -- k ) A.Delete(i, n + a[i][j][k]);
            }
            g[i] = g[i - 1];
            ans1[i] = m + 1;
    Next : ; 
        }
        
        REP(i, 1, n) printf("%lld ", ans1[i]); puts("");
        REP(i, 1, n)
        {
            int l = 1, r = i, pos = i;
            while ( l <= r ) 
            {
                int Mid = (l + r) >> 1;
                if ( Check(Mid, i) ) { pos = i - Mid; l = Mid + 1; }
                else r = Mid - 1;
            }
            printf("%lld ", pos);
        }
        puts("");
    }
    return 0;
}

