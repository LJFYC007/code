/***************************************************************
	File name: CF528C.cpp
	Author: ljfcnyali
	Create time: 2021年01月26日 星期二 21时54分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, deg[maxn], Begin[maxn], Next[maxn], To[maxn], e = 1, now;
vector<int> p;
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ deg[u]; } 

inline void DFS(int u, int op)
{
    for ( int &i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( vis[i] ) continue ;
        vis[i] = vis[i ^ 1] = true;
        DFS(v, op ^ 1); 
        if ( (++ now) & 1 ) { printf("%d %d\n", u, v); ++ deg[v]; }
        else { printf("%d %d\n", v, u); ++ deg[u]; }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); } 
    REP(i, 1, n) if ( deg[i] & 1 ) p.push_back(i);
    for ( int i = 0; i < p.size(); i += 2 ) { add(p[i], p[i + 1]); add(p[i + 1], p[i]); ++ m; }
    if ( m & 1 ) { add(1, 1); add(1, 1); ++ m; } printf("%d\n", m);
    DFS(1, 1);
    return 0;
}
