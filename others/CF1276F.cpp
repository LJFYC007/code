/***************************************************************
	File name: CF1276F.cpp
	Author: ljfcnyali
	Create time: 2020年10月15日 星期四 21时25分08秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 4e5 + 10;

int n, dfn[maxn], id[maxn], tot, ret;
int dis[maxn], anc[maxn][20], ans, g[maxn], val[maxn];
set<int> Set[maxn];
char s[maxn];
struct SAM
{
    struct node { int len, fa, Next[26]; } Tree[maxn]; 
    int lst = 1, tot = 1, Begin[maxn], Next[maxn], To[maxn], e;
    bool op;

    inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

    inline void Update(int pos, int num)
    {
        if ( op == 0 && num == n ) return ;
        if ( op == 1 && num == 1 ) return ;
        ans += Tree[pos].len - Tree[Tree[pos].fa].len;
    }

    inline void Extand(int c, int x)
    {
        int cur = ++ tot, p = lst; lst = cur; Tree[cur].len = Tree[p].len + 1; 
        if ( op == 0 ) Set[tot].insert(x);
        else g[x] = tot;
        while ( p && !Tree[p].Next[c] ) { Tree[p].Next[c] = cur; p = Tree[p].fa; }
        if ( !p ) { Tree[cur].fa = 1; Update(cur, x); return ; }
        int q = Tree[p].Next[c];
        if ( Tree[p].len + 1 == Tree[q].len ) { Tree[cur].fa = q; Update(cur, x); return ; }
        int clone = ++ tot; Tree[clone] = Tree[q]; Tree[clone].len = Tree[p].len + 1;
        while ( p && Tree[p].Next[c] == q ) { Tree[p].Next[c] = clone; p = Tree[p].fa; }
        Tree[q].fa = Tree[cur].fa = clone; Update(cur, x);
    }

    inline void Build() { REP(i, 2, tot) add(Tree[i].fa, i); }
} A, B;

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int i = 18; i >= 0; -- i ) if ( dis[anc[x][i]] >= dis[y] ) x = anc[x][i];
    if ( x == y ) return x;
    for ( int i = 18; i >= 0; -- i ) if ( anc[x][i] != anc[y][i] ) { x = anc[x][i]; y = anc[y][i]; }
    return anc[x][0];
}

inline void DFS1(int u)
{
    dfn[u] = ++ tot; id[tot] = u; 
    REP(j, 1, 18) anc[u][j] = anc[anc[u][j - 1]][j - 1];
    for ( int i = B.Begin[u]; i; i = B.Next[i] ) 
    {
        int v = B.To[i]; 
        anc[v][0] = u; dis[v] = dis[u] + 1;
        DFS1(v);
    }
}

inline int Get(int x) { return B.Tree[x].len; }

inline void DFS2(int u)
{
    Set[0] = Set[u]; Set[u].clear();
    for ( auto it : Set[0] ) if ( it + 2 <= n ) 
    {
        int x = dfn[g[it + 2]];
        Set[u].insert(x); val[u] += Get(g[it + 2]);
    }
    for ( int i = A.Begin[u]; i; i = A.Next[i] ) 
    {
        int v = A.To[i]; DFS2(v);
        if ( Set[v].size() > Set[u].size() ) { swap(Set[u], Set[v]); swap(val[u], val[v]); }
        for ( auto it : Set[v] ) 
        {
            auto j = Set[u].lower_bound(it);
            if ( j == Set[u].end() ) 
            {
                val[u] += Get(id[it]); 
                if ( j != Set[u].begin() )
                {
                    -- j;
                    val[u] -= Get(LCA(id[*j], id[it]));
                }
                Set[u].insert(it);
            }
            else if ( *j != it )
            {
                auto itr = j, itl = j; 
                val[u] += Get(id[it]) - Get(LCA(id[*itr], id[it]));
                if ( itr != Set[u].begin() ) 
                {
                    -- itl;
                    val[u] += Get(LCA(id[*itl], id[*itr]));
                    val[u] -= Get(LCA(id[*itl], id[it]));
                }
                Set[u].insert(it);
            }
        }
    }
    int x = A.Tree[u].len - A.Tree[A.Tree[u].fa].len;
    ans += x; ret += val[u] * x;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s + 1); n = str(s + 1);
    B.op = true;
    REP(i, 1, n) A.Extand(s[i] - 'a', i);
    for ( int i = n; i >= 1; -- i ) B.Extand(s[i] - 'a', i);
    A.Build(); B.Build();
    dis[1] = 1; DFS1(1); DFS2(1);
    ans = ans + 2 + ret;
    printf("%lld\n", ans);
    return 0;
}
