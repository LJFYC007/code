/***************************************************************
	File name: league.cpp
	Author: ljfcnyali
	Create time: 2020年11月17日 星期二 10时13分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3e5 + 10;

int n, Begin[maxn], Next[maxn << 1], To[maxn << 1], e, Min, X, Y, Max, pos;
int anc[maxn][19], number, dis[maxn], f[maxn];
pii Edge[maxn], s, t, g[maxn], suf[maxn];
vector<int> ans;
map<pii, int> Map;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    if ( dis[u] > Max ) { Max = dis[u]; pos = u; } 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        if ( X == u && v == Y ) continue ;
        if ( X == v && u == Y ) continue ;
        dis[v] = dis[u] + 1; f[v] = u; DFS(v, u);
    }
}

inline int Solve(int x, int &t)
{
    Max = -1; dis[x] = 0; DFS(x, 0); 
    Max = -1; dis[pos] = 0; DFS(pos, 0);
    int num = (Max + 1) / 2; t = pos;
    while ( num ) { t = f[t]; -- num; }
    return Max;
}

inline void DFS1(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; anc[v][0] = u; DFS1(v, u);
    }
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int i = 18; i >= 0; -- i ) if ( dis[anc[x][i]] >= dis[y] ) x = anc[x][i];
    if ( x == y ) return x;
    for ( int i = 18; i >= 0; -- i ) if ( anc[x][i] != anc[y][i] ) { x = anc[x][i]; y = anc[y][i]; } 
    return anc[x][0];
}

inline int Dis(int x, int y) { return dis[x] + dis[y] - 2 * dis[LCA(x, y)]; }

#define x first
#define y second
inline pii Maintain(pii a, pii b)
{
    pii t = a; int Max = Dis(a.x, a.y);
    int x = Dis(a.x, b.x); if ( x > Max ) { Max = x; t = pii(a.x, b.x); }
    x = Dis(a.x, b.y); if ( x > Max ) { Max = x; t = pii(a.x, b.y); }
    x = Dis(a.y, b.x); if ( x > Max ) { Max = x; t = pii(a.y, b.x); }
    x = Dis(a.y, b.y); if ( x > Max ) { Max = x; t = pii(a.y, b.y); }
    x = Dis(b.x, b.y); if ( x > Max ) { Max = x; t = pii(b.x, b.y); }
    return t;
}

inline void DFS2(int u, int fa)
{
    g[u] = pii(u, u); vector<int> p;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        p.push_back(v); DFS2(v, u); g[u] = Maintain(g[u], g[v]);
    }
    if ( !p.size() ) return ;
    int m = p.size(); suf[p[m - 1]] = pii(u, u);
    for ( int i = m - 2; i >= 0; -- i )
        suf[p[i]] = Maintain(g[p[i + 1]], suf[p[i + 1]]);
}

inline void DFS3(int u, int fa, pii now)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        pii t = Maintain(now, suf[v]); 
        now = Maintain(now, g[v]); DFS3(v, u, t);
        int len1 = Dis(g[v].x, g[v].y), len2 = Dis(t.x, t.y);
        int x = max((len1 + 1) / 2 + (len2 + 1) / 2 + 1, max(len1, len2));
        if ( x < Min ) { Min = x; ans.clear(); ans.push_back(Map[pii(u, v)]); number = Map[pii(u, v)]; }
        else if ( x == Min ) ans.push_back(Map[pii(u, v)]);
    }
}

int main()
{
    freopen("league.in", "r", stdin);
    freopen("league.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n - 1) 
    { 
        int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); 
        Edge[i] = pii(u, v); Map[pii(u, v)] = Map[pii(v, u)] = i;
    }
    dis[1] = 1; DFS1(1, 0); REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    Min = n - 1; DFS2(1, 0); DFS3(1, 0, pii(1, 1));
    printf("%d\n", Min);
    sort(ans.begin(), ans.end());
    printf("%d ", (int)ans.size()); for ( auto it : ans ) printf("%d ", it); puts("");
    X = Edge[number].first; Y = Edge[number].second;
    int pos1, pos2; Solve(X, pos1); Solve(Y, pos2); s = Edge[number]; t = pii(pos1, pos2);
    printf("%d %d %d %d\n", X, Y, pos1, pos2);
    return 0;
}
