/***************************************************************
	File name: HaHa
	Author: ljfcnyali
	Create time: 2020年05月07日 11时52分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, d[maxn];
int ans, f[maxn], t[maxn], g[maxn], Min[maxn];
vector<int> Edge[maxn];
bool vis[maxn];
queue<int> Q;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ d[v]; ++ g[u]; }

inline void DFS(int u)
{
    for ( auto v : Edge[u])
    {
        Min[v] = min(Min[v], u);
        DFS(v);
    }
    if ( f[u] == 0 && Min[u] > u ) { t[u] = 1; ++ ans; }
}

int main()
{
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); Edge[v].push_back(u); }  
    REP(i, 1, n) if ( d[i] == 0 ) Q.push(i); 
    REP(i, 1, n) f[i] = d[i];
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; -- d[v];
            if ( d[v] == 0 ) Q.push(v);
        }
    }
    REP(i, 1, n) if ( d[i] > 0 ) { puts("-1"); return 0; }
    REP(i, 1, n) Min[i] = n + 1;
    REP(i, 1, n) if ( !g[i] ){ cerr << i << endl;  DFS(i);}
    printf("%d\n", ans);
    REP(i, 1, n) printf("%c", t[i] == 1 ? 'A' : 'E'); puts("");
    return 0;
}
