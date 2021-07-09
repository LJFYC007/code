/***************************************************************
	File name: mst.cpp
	Author: ljfcnyali
	Create time: 2020年09月13日 星期日 10时28分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2010;

int n, m, k, f[maxn], vis[maxn], cnt;
struct node 
{ 
    int u, v, w; 
    bool operator < (const node &a) const { return w < a.w; } 
} Edge[maxn];
struct Node
{
    int pos, ret, Edge[51];
    vector<int> a;
    bool operator < (const Node &a) const { return ret > a.ret; } 
} p1, p2;
priority_queue<Node> Q;

inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

inline bool Kruskal(Node &p)
{
    ++ cnt;
    p.ret = 0; int num = 0; REP(i, 1, n) f[i] = i;
    REP(i, 1, m) if ( vis[i] == 1 ) 
    { 
        int fx = find(Edge[i].u), fy = find(Edge[i].v); 
        f[fx] = fy; p.ret += Edge[i].w; p.Edge[++ num] = i;
    }
    REP(i, p.pos + 1, m) 
    {
        int fx = find(Edge[i].u), fy = find(Edge[i].v); 
        if ( fx != fy ) { f[fx] = fy; p.ret += Edge[i].w; p.Edge[++ num] = i; }
    }
    if ( num != n - 1 ) return false;
    return true;
}

int main()
{
    freopen("mst.in", "r", stdin);
    freopen("mst.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &k);
    REP(i, 1, m) scanf("%d%d%d", &Edge[i].u, &Edge[i].v, &Edge[i].w);
    sort(Edge + 1, Edge + m + 1);
    Kruskal(p1); Q.push(p1);
    while ( !Q.empty() ) 
    {
        p1 = Q.top(); Q.pop(); -- k;
        if ( !k ) { printf("%d\n", p1.ret); cerr << cnt << endl; return 0; }
        REP(i, 1, m) vis[i] = 0;
        REP(i, 1, n - 1) if ( p1.Edge[i] < p1.pos ) vis[p1.Edge[i]] = 1;
        REP(i, 1, n - 1)
        {
            if ( p1.Edge[i] < p1.pos ) continue ;
            p2.pos = p1.Edge[i]; if ( Kruskal(p2) ) Q.push(p2);
            vis[p1.Edge[i]] = 1; 
        }
    }
    puts("-1");
    return 0;
}
