/***************************************************************
	File name: CF343E.cpp
	Author: ljfcnyali
	Create time: 2020年11月09日 星期一 10时16分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2010;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
vector<pii> Edge[maxn];
struct node 
{ 
    int u, v, w; 
    node ( int a = 0, int b = 0, int c = 0 ) { u = a; v = b; w = c; }
} ;
vector<node> egde;
bool vis[maxn];

inline void add(int u, int v, int w) 
{ 
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; 
    swap(u, v);
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; 
}

inline void BFS(

inline void Build(vector<int> a)
{
    if ( a.size() == 1 ) return ; 
    e = 1; mem(Begin); mem(vis); for ( auto it : a ) vis[it] = true;
    int s = a[0], t = a[1];
    for ( auto it : a ) for ( auto v : Edge[it] ) if ( vis[v.first] ) add(it, v.first, v.second);
    int flow = 0;
    while ( BFS(s, t) ) while ( int x = DFS(s, t, INF) ) flow += x;
    edge.push_back(node(s, t, flow));
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, m) { int u, v, w; scanf("%d%d%d", &u, &v, &w); Edge[u].push_back(pii(v, w)); }
    vector<int> a; REP(i, 1, n) a.push_back(i);
    Build(a);
    return 0;
}
