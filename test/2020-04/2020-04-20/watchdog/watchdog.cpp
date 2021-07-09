/***************************************************************
	File name: watchdog.cpp
	Author: ljfcnyali
	Create time: 2020年04月20日 星期一 19时17分06秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 998244353;

int n, N, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], L[maxn], R[maxn], ll, rr;
int md[maxn], son[maxn], val[maxn], tot, dis[maxn], Root[maxn], Rub[maxn], head;
LL ans[maxn], MAX;
struct node { int lson, rson; LL lazy, Max; } Tree[maxn << 2];
/*
int *g[maxn], mem[maxn], *now, head, tail;
pii Stack[maxn];
*/

//inline LL max(LL a, LL b) { return a < b ? b : a; }

inline int NewNode()
{
    int x;
    if ( head > 0 ) 
    {
        x = Rub[head --];
        ls(x) = rs(x) = Tree[x].Max = Tree[x].lazy = 0;
    }
    else x = ++ tot;
    return x;
}

inline void PushDown(const int root)
{
    if ( !Tree[root].lazy ) return ;
    if ( !ls(root) ) ls(root) = NewNode();
    if ( !rs(root) ) rs(root) = NewNode();
    Tree[ls(root)].lazy += Tree[root].lazy; Tree[ls(root)].Max += Tree[root].lazy;
    Tree[rs(root)].lazy += Tree[root].lazy; Tree[rs(root)].Max += Tree[root].lazy;
    Tree[root].lazy = 0;
}

inline void Modify(int &root, int l, int r, const int val)
{
    if ( !root ) root = NewNode();
    if ( ll <= l && r <= rr ) { Tree[root].Max += val; Tree[root].lazy += val; return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( ll <= Mid ) Modify(ls(root), l, Mid, val);
    if ( Mid < rr ) Modify(rs(root), Mid + 1, r, val);
    Tree[root].Max = max(Tree[ls(root)].Max, Tree[rs(root)].Max);
}

inline int Merge(int p, int q, int l, int r)
{
    if ( !p || !q ) return p + q;
    int root = NewNode(); Tree[root].Max = max(Tree[p].Max, Tree[q].Max);
    if ( l == r ) 
    {
        Rub[++ head] = p; Rub[++ head] = q;
        return root;
    }
    int Mid = l + r >> 1; PushDown(p); PushDown(q);
    int l1 = ls(p), l2 = ls(q), r1 = rs(p), r2 = rs(q);
    Rub[++ head] = p; Rub[++ head] = q;
    ls(root) = Merge(l1, l2, l, Mid);
    rs(root) = Merge(r1, r2, Mid + 1, r);
    return root;
}

inline void Query(int root, int l, int r)
{
    if ( !root || Tree[root].Max <= MAX ) return ;
    if ( ll <= l && r <= rr ) { MAX = Tree[root].Max; return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( ll <= Mid ) Query(ls(root), l, Mid);
    if ( Mid < rr) Query(rs(root), Mid + 1, r);
}

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void DFS1(int u, int fa)
{
    md[u] = dis[u];
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; DFS1(v, u); 
        md[u] = max(md[u], md[v]);
		if ( !son[u] || md[v] > md[son[u]] ) { son[u] = v; val[u] = W[i]; }
    }
}

inline void DFS2(int u, int fa)
{
    if ( son[u] ) 
    {
        DFS2(son[u], u);
        Root[u] = Root[son[u]];
        ll = dis[u] + 1; rr = md[u]; Modify(Root[u], 1, N, val[u]);
        int l = max(dis[u], dis[u] + L[u]), r = min(md[u], dis[u] + R[u]);
        if ( l <= r ) 
        {
            MAX = max(0ll, ans[u]); ll = l; rr = r; Query(Root[u], 1, N);
            ans[u] = max(ans[u], MAX);
        }
    }
    else Root[u] = ++ tot;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || v == son[u] ) continue ;
        DFS2(v, u);
        ll = dis[v]; rr = md[v]; Modify(Root[v], 1, N, W[i]);

        REP(j, dis[v], md[v]) 
        {
            if ( j > dis[u] + R[u] ) break ; 
            int l = max(dis[u], dis[u] + dis[u] + L[u] - j), r = min(md[u], dis[u] + dis[u] + R[u] - j);
            if ( l <= r ) 
            {
                MAX = 0;
                ll = j; rr = j; Query(Root[v], 1, N); 
                LL sum = MAX; MAX = max(0ll, ans[u] - MAX);
                ll = l; rr = r; Query(Root[u], 1, N); 
                ans[u] = max(ans[u], sum + MAX);
            }
            /*
            if ( j + 1 > R[u] ) break ; 
            if ( L[u] <= j + 1 && j + 1 <= R[u] ) ans[u] = max(ans[u], g[v][j] + W[i]);     
            int l = max(0ll, L[u] - j - 1), r = min(md[u] + 1, R[u] - j - 1);
            while ( head <= tail && (Stack[head].second > r || Stack[head].second < l) ) ++ head;
            while ( head <= tail && Stack[tail].first <= g[u][l] ) -- tail;
            Stack[++ tail] = pii(g[u][l], l);
            if ( head <= tail ) ans[u] = max(ans[u], g[v][j] + W[i] + Stack[head].first);
            */
        }
        Root[u] = Merge(Root[u], Root[v], 1, N);
    }
}

/*
inline void DFS2(int u, int fa)
{
    if ( son[u] ) 
    {
        g[son[u]] = g[u] + 1;
        DFS2(son[u], u);
        REP(j, 0, md[son[u]]) 
        {
            g[u][j + 1] += val[u];
            if ( L[u] <= j + 1 && j + 1 <= R[u] ) ans[u] = max(ans[u], g[u][j + 1]);
        }
    }
    g[u][0] = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || v == son[u] ) continue ;
		g[v] = now; now += md[v] + 1;
		DFS2(v, u);

        head = 1; tail = 0; 
        int l = max(0ll, L[u] - 1), r = min(md[u] + 1, R[u] - 1);
        for ( int j = r; j >= l; -- j )
        {
            while ( head <= tail && Stack[tail].first <= g[u][j] ) -- tail;
            Stack[++ tail] = pii(g[u][j], j);
        }
         
        REP(j, 0, md[v]) 
        {
            if ( j + 1 > R[u] ) break ; 
            if ( L[u] <= j + 1 && j + 1 <= R[u] ) ans[u] = max(ans[u], g[v][j] + W[i]);     
            int l = max(0ll, L[u] - j - 1), r = min(md[u] + 1, R[u] - j - 1);
            while ( head <= tail && (Stack[head].second > r || Stack[head].second < l) ) ++ head;
            while ( head <= tail && Stack[tail].first <= g[u][l] ) -- tail;
            Stack[++ tail] = pii(g[u][l], l);
            if ( head <= tail ) ans[u] = max(ans[u], g[v][j] + W[i] + Stack[head].first);
        }
		REP(j, 0, md[v]) g[u][j + 1] = max(g[u][j + 1], g[v][j] + W[i]);
    }
}
*/

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

int main()
{
    freopen("watchdog.in", "r", stdin);
    freopen("watchdog.out", "w", stdout);
    read(n);
    REP(i, 1, n) { ans[i] = -1; read(L[i]); read(R[i]); }
    REP(i, 2, n) { int x, w; read(x); read(w); add(x, i, w); }
    dis[1] = 1; DFS1(1, 0); N = md[1];
    DFS2(1, 0);
    /*
	now = mem + 1;
	g[1] = now; now += md[1] + 1;
    DFS2(1, 0);
    */
//    REP(i, 1, n) printf("%lld ", ans[i]); puts("");
    LL ret = 0, x = 1;
    for ( int i = n; i >= 1; -- i ) 
    {
        ans[i] %= Mod;
        ret = (ret + x * ans[i]) % Mod;
        x = x * 23333 % Mod;
    }
    printf("%lld\n", (ret + Mod) % Mod);
//    cerr << tot << endl;
    return 0;
}
