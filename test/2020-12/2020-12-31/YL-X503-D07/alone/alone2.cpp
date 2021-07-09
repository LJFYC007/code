/***************************************************************
	File name: alone2.cpp
	Author: ljfcnyali
	Create time: 2020年12月31日 星期四 10时49分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, f[maxn][2];
vector<int> p, q;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    f[u][1] = 1; f[u][0] = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u);
        f[u][1] += f[v][0];
        f[u][0] += max(f[v][1], f[v][0]);
    }
}

inline void Get(int u, int op, int fa)
{
    if ( op ) cout << u << endl;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        if ( op == 1 ) Get(v, 0, u);
        else if ( f[v][1] > f[v][0] ) Get(v, 1, u);
        else Get(v, 0, u);
    }
}

int main()
{
    int op; scanf("%d", &op);
    scanf("%d%d", &n, &m);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    DFS(1, 0);
    cout << max(f[1][1], f[1][0]) << endl;
    if ( f[1][1] > f[1][0] ) Get(1, 1, 0);
    else Get(1, 0, 0);
    return 0;
}
