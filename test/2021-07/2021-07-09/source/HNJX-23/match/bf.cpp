#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define pii pair<int, int>

const int maxn = 5010;
const int maxm = 6010;
const int INF = 0x3f3f3f3f;

int n, m, a[maxn], b[maxn], c[maxn][maxn], sum, ans = INF, E;
int Begin[maxm], Next[maxm], To[maxm], e, From[maxm], W[maxm], F[maxm], dis[maxn], Min[maxn], pre[maxn];
struct node { int a, b, c, d, e, f; } Last[maxm];
vector<int> p; bool vis[maxn]; queue<int> Q;

inline void add(int u, int v, int w, int f)
{
    To[++ e] = v; From[e] = u; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; F[e] = f;
    swap(u, v); w = 0; f = -f;
    To[++ e] = v; From[e] = u; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; F[e] = f;
}

inline bool BFS(int s, int t)
{
    REP(i, 1, t) { dis[i] = INF; vis[i] = false; } 
    dis[s] = 0; Min[s] = INF; vis[s] = true; Q.push(s);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] ) if ( W[i] ) 
        {
            int v = To[i]; 
            if ( dis[v] > dis[u] + F[i] ) 
            {
                dis[v] = dis[u] + F[i]; pre[v] = i;
                Min[v] = min(Min[u], W[i]);
                if ( !vis[v] ) { vis[v] = true; Q.push(v); }
            }
        }
        vis[u] = false;
    }
    return dis[t] != INF;
}

inline void Solve(int s, int t, int &ret, int &flow)
{
    int x = t; ret += Min[t] * dis[t]; flow += Min[t];
    while ( x != s ) 
    {
        int i = pre[x];
        W[i] -= Min[t]; W[i ^ 1] += Min[t];
        x = From[i];
    }
}

signed main()
{
    freopen("match.in", "r", stdin);
    freopen("match.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) 
    { 
        int x; scanf("%d", &x); sum += x;
        if ( x & 1 ) { -- x; p.push_back(i); ++ m; }
        a[i] = b[i] = x / 2;
    }
    REP(i, 1, n) REP(j, 1, n) scanf("%d", &c[i][j]);
    if ( sum & 1 ) { puts("-1"); return 0; }

    int s = n + n + 1, t = n + n + 2; e = 1;
    REP(i, 1, n) { add(s, i, a[i], 0); add(n + i, t, b[i], 0); }
    REP(i, 1, n) REP(j, 1, n) add(i, n + j, INF, c[i][j]);
    int ret = 0, flow = 0;
    while ( BFS(s, t) ) Solve(s, t, ret, flow);
    E = e;
    REP(i, 1, e) Last[i] = {Begin[i], Next[i], To[i], From[i], W[i], F[i]};

    REP(o, 0, (1 << m) - 1)
    {
        int x = 0;
        REP(i, 0, m - 1) if ( (o >> i) & 1 ) ++ x; else -- x;
        if ( x != 0 ) continue ;

        int X = ret, Y = flow; // e = E;
        //REP(i, 1, e) { Begin[i] = Last[i].a; Next[i] = Last[i].b; To[i] = Last[i].c; From[i] = Last[i].d; W[i] = Last[i].e; F[i] = Last[i].f; }
        REP(i, 0, m - 1) if ( (o >> i) & 1 ) add(s, p[i], 1, 0); else add(n + p[i], t, 1, 0);
        while ( BFS(s, t) ) Solve(s, t, X, Y);
        return 0;
        
        if ( Y == sum / 2 ) ans = min(ans, X);
    }
    printf("%d\n", ans);
    return 0;
}