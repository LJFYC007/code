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
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 400010;
const LL Mod = 1e9 + 7;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, m, s, t, cnt, Root[maxn * 100], Max = 1e5 + 100, opt; 
LL ans, p[maxn];
bool vis[maxn], flag;

struct node
{
    int lson, rson;
    LL val;
} Tree[maxn * 100];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void Push_up(int root, int len)
{
    Tree[root].val = (Tree[ls(root)].val + (p[len] * Tree[rs(root)].val) % Mod) % Mod;
}

inline void Insert(int now, int &root, int l, int r, int val)
{
    root = ++ cnt; Tree[root] = Tree[now];
    // cerr << root << endl;
    if ( l == r ) { if ( !Tree[root].val ) { Tree[root].val = 1; flag = true; } else Tree[root].val = 0; return ; }
    int Mid = l + r >> 1;
    if ( val <= Mid ) { Insert(ls(now), ls(root), l, Mid, val); if ( flag == false ) val = Mid + 1; }
    if ( val > Mid ) Insert(rs(now), rs(root), Mid + 1, r, val);
    Push_up(root, Mid - l + 1);
}

inline bool cmp(int p, int q, int l, int r)
{
    if ( l == r ) return Tree[p].val < Tree[q].val;
    if ( Tree[p].val == Tree[q].val ) return true;
    int Mid = l + r >> 1;
    if ( Tree[rs(p)].val == Tree[rs(q)].val ) return cmp(ls(p), ls(q), l, Mid);
    return cmp(rs(p), rs(q), Mid + 1, r);
}

struct Node
{
    int pos, root;
    bool operator < (const Node &a) const { return !cmp(root, a.root, 0, Max); }
} p1, p2;

priority_queue<Node> Q;

int main()
{
    freopen("physics.in", "r", stdin);
    freopen("physics.out", "w", stdout);
    scanf("%d", &opt);
    scanf("%d%d%d%d", &n, &m, &s, &t);
    REP(i, 1, m) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); }
    p[0] = 1; REP(i, 1, Max + 1) p[i] = (p[i - 1] * 2) % Mod;
    REP(i, 1, n) 
    {
        if ( i == s ) continue ;
        flag = false;
        Insert(0, Root[i], 0, Max, Max);
    }
    p1.pos = s; p1.root = 0; Q.push(p1);
    while ( !Q.empty() )
    {
        int u = Q.top().pos; Q.pop();
        if ( vis[u] ) continue ; vis[u] = true;
        if ( u == t ) break ;
        for ( int i = Begin[u]; i; i = Next[i] )
        {
            int v = To[i], now = 0;
            flag = false;
            Insert(Root[u], now, 0, Max, W[i]);
            if ( cmp(now, Root[v], 0, Max) )
            {
                Root[v] = now; p2.pos = v; p2.root = now; Q.push(p2);
            }
        }
    }
    if ( !vis[t] ) puts("-1");
    else printf("%lld\n", Tree[Root[t]].val);
    return 0;
}
