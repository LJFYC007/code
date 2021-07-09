/***************************************************************
    File name: C.cpp
    Author: ljfcnyali
    Create time: 2020年07月12日 星期日 09时28分22秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
 
const int maxn = 2e6 + 10;
const LL INF = 1e18;
 
int n, m, tot = 1, ans, fail[maxn], Begin[maxn], Next[maxn], To[maxn], e;
LL f[maxn], g[maxn];
char s[maxn];
struct node { int Next[26]; LL val; } Trie[maxn], Tree[maxn];
 
inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }
 
inline void Insert(int x)
{
    int p = 1;
    REP(i, 1, str(s + 1))
    {
        int c = s[i] - 'a';
        if ( !Trie[p].Next[c] ) Trie[p].Next[c] = ++ tot; 
        p = Trie[p].Next[c];
    }
    Trie[p].val += x;
}
 
inline void BFS()
{
    REP(i, 1, tot) Tree[i] = Trie[i];
    REP(i, 1, tot) REP(j, 0, 25) if ( Trie[i].Next[j] ) add(i, Trie[i].Next[j]);
    queue<int> Q; Q.push(1);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop(); Trie[u].val += Trie[fail[u]].val;
        REP(i, 0, 25)
        {
            if ( !Trie[u].Next[i] ) { Trie[u].Next[i] = Trie[fail[u]].Next[i]; continue ; }
            fail[Trie[u].Next[i]] = Trie[fail[u]].Next[i];
            Q.push(Trie[u].Next[i]);
        }
    }
    Q.push(1);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        REP(i, 0, 25)
        {
            int v = Tree[u].Next[i]; if ( !v ) continue ; Q.push(v);
            g[v] = g[u] + Trie[v].val; f[v] = max(f[u], -INF); 
            int x = fail[u]; 
            while ( x && Tree[x].Next[i] != fail[v] ) { f[v] = max(f[v], max(g[x], f[x])); x = fail[x]; }
            f[v] += Trie[fail[v]].val; 
        }
    }
    Q.push(1);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        f[u] = max(f[u], f[fail[u]]);
        f[u] = max(f[u], g[u]);
        for ( int i = Begin[u]; i; i = Next[i] ) Q.push(To[i]);
    }
}
 
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 0, 25) Trie[0].Next[i] = 1;
    REP(i, 1, n) { int x; scanf("%s %d", s + 1, &x); Insert(x); }
    scanf("%s", s + 1); Insert(0);
    BFS();
    int p = 1; LL ans = 0;
    REP(i, 1, m)
    {
        p = Trie[p].Next[s[i] - 'a'];
        ans = max(ans, f[p]);
    }
    printf("%lld\n", ans);
    return 0;
}
