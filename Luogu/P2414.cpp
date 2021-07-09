/***************************************************************
	File name: P2414.cpp
	Author: ljfcnyali
	Create time: 2019年10月20日 星期日 09时36分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 200010;

int n, m, tot, Fail[maxn], Begin[maxn], Next[maxn], To[maxn], e;
int dfn[maxn], cnt, ans[maxn], size[maxn], c[maxn], t[maxn], num;
vector<pii> q[maxn];
char s[maxn];
struct node 
{ 
    int next[26], Next[26], fa; bool finish;
} Trie[maxn];

inline int lowbit(int x) { return x & -x; }

inline void Modify(int pos, int val)
{
    for ( int i = pos; i <= tot; i += lowbit(i) ) c[i] += val;
}

inline int Query(int pos)
{
    int sum = 0;
    for ( int i = pos; i > 0; i -= lowbit(i) ) sum += c[i];
    return sum;
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Build()
{
    REP(i, 0, 25) Trie[0].next[i] = 1;
    int p = ++ tot;
    REP(i, 1, n)
    {
        if ( s[i] >= 'a' && s[i] <= 'z' ) 
        {
            char c = s[i] - 'a';
            if ( !Trie[p].next[c] ) Trie[p].next[c] = ++ tot;
            Trie[p].Next[c] = Trie[p].next[c];
            Trie[Trie[p].next[c]].fa = p; p = Trie[p].next[c];
        }
        else if ( s[i] == 'B' ) p = Trie[p].fa;
        else { t[++ num] = p; Trie[p].finish = true; }
    }
    queue<int> Q; Q.push(1);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        REP(i, 0, 25)
        {
            if ( !Trie[u].next[i] ) { Trie[u].next[i] = Trie[Fail[u]].next[i]; continue ; }
            Fail[Trie[u].next[i]] = Trie[Fail[u]].next[i];
            Q.push(Trie[u].next[i]);
        }
    }
    REP(i, 1, tot) add(Fail[i], i);
}

inline void DFS(int u, int fa)
{
    size[u] = 1; dfn[u] = ++ cnt;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u);
        size[u] += size[v];
    }
}

inline void Solve(int u, int fa)
{
    Modify(dfn[u], 1);
    if ( Trie[u].finish ) 
    {
        // printf("%d %d\n", u, q[u].size());
        for ( auto i : q[u] ) 
        {
            // printf("%d %d %d %d\n", u, i.first, size[i.first], i.second);
            ans[i.second] = Query(dfn[i.first] + size[i.first] - 1) - Query(dfn[i.first] - 1);
        }
    }
    REP(i, 0, 25) if ( Trie[u].Next[i] ) Solve(Trie[u].Next[i], u);
    Modify(dfn[u], -1);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s + 1); n = str(s + 1); 
    Build(); DFS(1, 0);
    scanf("%d", &m);
    REP(i, 1, m) 
    {
        int x, y; scanf("%d%d", &x, &y);
        q[t[y]].push_back(make_pair(t[x], i));
    }
    // REP(i, 1, tot) printf("%d ", q[i].size()); puts("");
    Solve(1, 0);
    REP(i, 1, m) printf("%d\n", ans[i]);
    return 0;
}
