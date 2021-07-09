/***************************************************************
	File name: CF1207G.cpp
	Author: ljfcnyali
	Create time: 2020年08月12日 星期三 16时08分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, q, Fail[maxn], Begin[maxn], Next[maxn], To[maxn], e, tot = 1;
int ans[maxn], dfn[maxn], m, c[maxn], size[maxn], id[maxn], belong[maxn];
struct node { int Next[26]; } Tree[maxn], Trie[maxn];
vector<int> p[maxn];
queue<int> Q;
char s[maxn];

inline int lowbit(int x) { return x & -x; }

inline void Modify(int pos, int val) { for ( int i = pos; i <= tot; i += lowbit(i) ) c[i] += val; }

inline int Query(int l, int r) 
{ 
    int ret = 0; 
    for ( int i = r; i > 0; i -= lowbit(i) ) ret += c[i]; 
    for ( int i = l - 1; i > 0; i -= lowbit(i) ) ret -= c[i]; 
    return ret; 
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u)
{
    dfn[u] = ++ m; size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) { DFS1(To[i]); size[u] += size[To[i]]; }
}

inline void DFS2(int u, int pos)
{
    Modify(dfn[pos], 1);
    for ( auto i : p[u] ) 
    {
        int x = belong[i];
        ans[i] = Query(dfn[x], dfn[x] + size[x] - 1);
    }
    REP(i, 0, 25)
    {
        if ( !Trie[u].Next[i] ) continue ;
        DFS2(Trie[u].Next[i], Tree[pos].Next[i]);
    }
    Modify(dfn[pos], -1);
}

inline void Insert(int x)
{
    int p = 1;
    REP(i, 1, str(s + 1))
    {
        int c = s[i] - 'a';
        if ( !Tree[p].Next[c] ) Tree[p].Next[c] = ++ tot;
        p = Tree[p].Next[c];
    }
    belong[x] = p;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    REP(i, 0, 25) Tree[0].Next[i] = 1;
    scanf("%d", &n);
    REP(i, 1, n)
    {
        int op, x; char c; scanf("%d ", &op);
        if ( op == 1 ) { scanf("%c", &c); x = 1; }
        else { scanf("%d %c", &x, &c); x = id[x]; }
        c -= 'a';
        if ( !Trie[x].Next[c] ) Trie[x].Next[c] = ++ tot;
        id[i] = Trie[x].Next[c];
    }
    tot = 1; scanf("%d", &q);
    REP(i, 1, q)
    {
        int x; scanf("%d %s", &x, s + 1);
        Insert(i); p[id[x]].push_back(i);
    }

    Q.push(1); 
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        REP(i, 0, 25)
        {
            if ( !Tree[u].Next[i] ) { Tree[u].Next[i] = Tree[Fail[u]].Next[i]; continue ; }
            Fail[Tree[u].Next[i]] = Tree[Fail[u]].Next[i];
            Q.push(Tree[u].Next[i]);
        }
    }
    REP(i, 2, tot) add(Fail[i], i);

    DFS1(1); DFS2(1, 1);
    REP(i, 1, q) printf("%d\n", ans[i]);
    return 0;
} 
