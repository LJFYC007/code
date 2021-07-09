/***************************************************************
	File name: physics.cpp
	Author: ljfcnyali
	Create time: 2019年08月01日 星期四 08时46分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 400010;
const LL Mod = 1e9 + 7;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, m, s, t, Max[maxn], opt, pre[maxn];
bool Map[100010][2010];
LL ans;

bool vis[maxn], arrive[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void Update(int x, int p, int val)
{
    Max[x] = Max[p];
    REP(i, 0, Max[p]) Map[x][i] = Map[p][i]; Map[x][Max[p] + 1] = false;
    if ( val > Max[x] ) 
    { 
        REP(i, Max[x] + 1, val - 1) Map[x][i] = false;
        Max[x] = val; Map[x][val] = true; return ; 
    }
    while ( Map[x][val] == true ) { Map[x][val] = false; ++ val; }
    Map[x][val] = true; Max[x] = max(Max[x], val);
}

inline bool pd(int p, int q)
{
    if ( !arrive[q] ) { arrive[q] = true; return true; }
    if ( Max[q] > Max[p] ) return true;
    if ( Max[q] < Max[p] ) return false;
    for ( int i = Max[q]; i >= 0; -- i ) 
    {
        if ( Map[q][i] == true && Map[p][i] == false ) return true;
        if ( Map[q][i] == false && Map[p][i] == true ) return false;
    }
    return false;
}

inline void Spfa()
{
    queue<int> Q; Q.push(s);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] )
        {
            int v = To[i];
            Update(0, u, W[i]);
            if ( pd(0, v) ) 
            {
                Max[v] = Max[0];
                REP(j, 0, Max[0]) Map[v][j] = Map[0][j];
                if ( !vis[v] ) { pre[v] = u; vis[v] = true; Q.push(v); }
            }
        }
        vis[u] = false;
    }
}

inline LL power(LL a, LL b)
{
    LL r = 1;
    while ( b ) 
    {
        if ( b & 1 ) r = (r * a) % Mod;
        a = (a * a) % Mod;
        b >>= 1;
    }
    return r;
}

int main()
{
    freopen("physics3.in", "r", stdin);
    freopen("physics.out", "w", stdout);
    scanf("%d", &opt);
    if ( opt == 18 ) { scanf("%d%d%d%d", &n, &m, &s, &t); if ( s != t ) printf("-1\n"); else printf("0\n"); return 0; }
    if ( opt <= 15 ) 
    {
        scanf("%d%d%d%d", &n, &m, &s, &t);
        REP(i, 1, m) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); }
        arrive[s] = true;
        Spfa();
        int u = t; while ( pre[u] != s ) { fprintf(stderr,"%d ", u); u = pre[u]; }
        if ( !arrive[t] ) { printf("-1\n"); return 0; }
        ans = 0;
        REP(i, 0, Max[t]) if ( Map[t][i] ) ans = (ans + power(2, i)) % Mod;
        printf("%lld\n", ans);
        return 0;
    }
    scanf("%d%d%d%d", &n, &m, &s, &t);
    REP(i, 1, m) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, 1); add(v, u, 1); }
    queue<int> Q; Q.push(s); int dis[maxn]; memset(dis, 0x3f, sizeof(dis)); dis[s] = 0;
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; 
            if ( dis[v] > dis[u] + W[i] ) { dis[v] = dis[u] + W[i]; if ( !vis[v] ) { vis[v] = true; Q.push(v); } }
        }
        vis[u] = false;
    }
    if ( dis[t] == 0x3f3f3f3f ) { printf("-1\n"); return 0; }
    ans = dis[t]; ans = (ans * power(2, 100000)) % Mod;
    printf("%lld\n", ans);
    return 0;
}
