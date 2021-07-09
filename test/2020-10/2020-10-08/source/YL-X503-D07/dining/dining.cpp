/***************************************************************
	File name: dining.cpp
	Author: ljfcnyali
	Create time: 2020年10月08日 星期四 08时56分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2010;
const int maxm = 3e4 + 10;
const int INF = 0x3f3f3f3f;
const int Mod = 1e9 + 9;

int n, m, S, T, Begin[maxm], Next[maxm], To[maxm], e, W[maxm];
int dis[maxn][maxn], f[maxn][maxn], a[maxn][maxn], id[maxn], st;
queue<int> Q;
bool vis[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline bool cmp(int x, int y) { return dis[st][x] < dis[st][y]; }

inline void Spfa(int s)
{
    REP(i, 1, n) { dis[s][i] = INF; vis[i] = false; }
    dis[s][s] = 0; Q.push(s); vis[s] = true;
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; 
            if ( dis[s][v] > dis[s][u] + W[i] ) 
            {
                dis[s][v] = dis[s][u] + W[i]; 
                if ( !vis[v] ) { vis[v] = true; Q.push(v); }
            }
        }
        vis[u] = false;
    }
    st = s; REP(i, 1, n) id[i] = i;
    sort(id + 1, id + n + 1, cmp);
    f[S][S] = 1;
    REP(i, 1, n)
    {
        int u = id[i];
        for ( int j = Begin[u]; j; j = Next[j] ) 
        {
            int v = To[j];
            if ( dis[s][u] + W[j] != dis[s][v] ) continue ; 
            REP(k, 1, n) 
            {
                if ( u == k && u != S ) continue ;
                if ( k == T && u == S && v == T ) continue ; 
                f[min(v, k)][max(v, k)] = (f[min(v, k)][max(v, k)] + f[min(u, k)][max(u, k)]) % Mod;
            }
        }
    }
    // REP(i, 1, n) REP(j, 1, n) printf("%d %d %d\n", i, j, f[i][j]);
}

int main()
{
    freopen("dining.in", "r", stdin);
    freopen("dining.out", "w", stdout);
    scanf("%d%d%d%d", &n, &m, &S, &T);    
    REP(i, 1, n) REP(j, 1, n) a[i][j] = INF;
    REP(i, 1, m) { int u, v, w; scanf("%d%d%d", &u, &v, &w); a[u][v] = min(a[u][v], w); }
    REP(i, 1, n) REP(j, 1, n) if ( a[i][j] != INF ) add(i, j, a[i][j]);

    Spfa(S);
    printf("%d\n", f[T][T] + (a[S][T] < INF));
    return 0;
}
