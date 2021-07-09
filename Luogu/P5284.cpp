/***************************************************************
	File name: P5284.cpp
	Author: ljfcnyali
	Create time: 2020年06月04日 星期四 16时12分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define x first
#define y second
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 2e6 + 10;
const int maxm = 5e6;

int T, n, N, m1, m2, m, tot, last, Begin[maxm], Next[maxm], To[maxm], e, ans, W[maxm], id[maxm], cnt;
int anc[maxn][20], f[maxn], a[maxn], b[maxn], dis[maxm], val[maxm], dfn[maxm], size[maxm], deg[maxm];
set<int> Edge[maxn];
set<tuple<int, int, int > > Set[maxn];
struct node { int Next[26], len, fa; } Trie[maxn];
char s[maxn];

inline void add(int u, int v, int w) { ++ deg[v]; To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void Build(int root, int l, int r)
{
    if ( l == r ) { id[l] = root; return ; }
    int Mid = l + r >> 1;
    Build(lson, l, Mid); Build(rson, Mid + 1, r);
    add(root, lson, 0); add(root, rson, 0);
}

inline void Modify(int root, int l, int r, int L, int R, int x, int val)
{
    if ( L <= l && r <= R ) { add(x, root, val); return ; }
    int Mid = l + r >> 1;
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, x, val);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, x, val);
}

inline void Extand(int c)
{
    int p = last, cur = ++ tot; last = tot; Trie[cur].len = Trie[p].len + 1;
    while ( p && !Trie[p].Next[c] ) { Trie[p].Next[c] = cur; p = Trie[p].fa; } 
    if ( !p ) { Trie[cur].fa = 1; return ; }
    int q = Trie[p].Next[c];
    if ( Trie[p].len + 1 == Trie[q].len ) { Trie[cur].fa = q; return ; }
    int clone = ++ tot;
    Trie[clone] = Trie[q]; Trie[clone].len = Trie[p].len + 1;
    while ( p && Trie[p].Next[c] == q ) { Trie[p].Next[c] = clone; p = Trie[p].fa; } 
    Trie[q].fa = Trie[cur].fa = clone;
}

inline void DFS(int u)
{
    dfn[u] = ++ cnt; size[u] = 1;
    for ( auto v : Edge[u] ) { DFS(v); size[u] += size[v]; }
}

inline int Get(int pos, int len)
{
    int p = f[pos];
    for ( int j = 18; j >= 0; -- j ) if ( Trie[anc[p][j]].len >= len ) p = anc[p][j];
    return p;
}

inline void read(int &x)
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &T);
    memset(dis, -1, sizeof(dis));
    while ( T -- )  
    {
        scanf("%s", s + 1); n = str(s + 1); reverse(s + 1, s + n + 1);
        // cerr << endl;
        // cerr << N << endl;
        REP(i, 1, N / 4) 
        { 
            Trie[i].len = Trie[i].fa = 0; 
            REP(j, 0, 25) Trie[i].Next[j] = 0;
            Edge[i].clear(); Set[i].clear();
        }
        REP(i, 0, N) 
        { 
            Begin[i] = deg[i] = 0; dis[i] = -1;
        }
        e = cnt = 0; tot = last = 1;
        REP(i, 1, n) { Extand(s[i] - 'a'); f[i] = last; }
        N = tot;
        REP(i, 1, N) { anc[i][0] = Trie[i].fa; Edge[Trie[i].fa].insert(i); }
        REP(j, 1, 18) REP(i, 1, N) anc[i][j] = anc[anc[i][j - 1]][j - 1];

        read(m1);
        REP(i, 1, m1) 
        { 
            int x, y; read(x); read(y);
            a[i] = Get(n - x + 1, y - x + 1); val[i] = y - x + 1; 
            Set[a[i]].insert(make_tuple(val[i], 1, i));
        }
        read(m2);
        REP(i, 1, m2) 
        { 
            int x, y; read(x); read(y);
            b[i] = Get(n - x + 1, y - x + 1); 
            Set[b[i]].insert(make_tuple(y - x + 1, 2, i));
        }
        // cerr << N << endl;
        REP(i, 1, N)
            for ( auto it = Set[i].begin(); it != Set[i].end(); ++ it ) 
            {
                if ( get<0>(*it) == Trie[anc[i][0]].len ) 
                {
                    if ( get<1>(*it) == 1 ) a[get<2>(*it)] = anc[i][0];
                    else b[get<2>(*it)] = anc[i][0];
                    continue ; 
                }
                if ( get<0>(*it) == Trie[i].len ) continue ;
                ++ N; Edge[anc[i][0]].erase(i); Edge[anc[i][0]].insert(N); 
                Edge[N].insert(i); anc[i][0] = N; Trie[N].len = get<0>(*it);
                if ( get<1>(*it) == 1 ) a[get<2>(*it)] = anc[i][0];
                else b[get<2>(*it)] = anc[i][0];
            }

        DFS(1); Build(1, 1, N);

        read(m);
        REP(i, 1, m) 
        {
            int x, y; read(x); read(y);
            Modify(1, 1, N, dfn[b[y]], dfn[b[y]] + size[b[y]] - 1, id[dfn[a[x]]], val[x]);
        }
        REP(i, 1, m1) Modify(1, 1, N, dfn[a[i]], dfn[a[i]], id[1], 0);
        // cerr << N << endl;

        N *= 4;
        queue<int> Q; REP(i, 1, N) if ( !deg[i] ) { dis[i] = 0; Q.push(i); }
        while ( !Q.empty() ) 
        {
            int u = Q.front(); Q.pop();
            for ( int i = Begin[u]; i; i = Next[i] ) 
            {
                int v = To[i]; -- deg[v];
                dis[v] = max(dis[v], dis[u] + W[i]);
                if ( !deg[v] ) Q.push(v);
            }
        }
        REP(i, 1, N) if ( deg[i] > 0 ) { puts("-1"); goto Next; }

        ans = 0;
        REP(i, 1, m1) ans = max(ans, dis[id[dfn[a[i]]]] + val[i]);
        printf("%lld\n", ans);
Next : ; 
    }
    return 0;
}
