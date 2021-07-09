/***************************************************************
	File name: chocolate.cpp
	Author: ljfcnyali
	Create time: 2020年09月16日 星期三 20时35分01秒
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

int n, m, tot, N, dfn[maxn], cnt, size[maxn], c[2][maxn];
pii a[maxn];
LL ans;
struct node { int Next[26]; } Trie[maxn];
char s[maxn];
vector<int> p, belong[maxn];

inline int lowbit(int x) { return x & -x; }

inline void Modify(int pos, int val, int op) { for ( int i = pos; i <= cnt; i += lowbit(i) ) c[op][i] += val; }

inline int Query(int pos, int op) { int ret = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) ret += c[op][i]; return ret; }

inline int Insert(int l, int r, int op)
{
    int p = 1;
    if ( op ) REP(i, l, r)
    {
        int c = s[i] - 'a';
        if ( !Trie[p].Next[c] ) Trie[p].Next[c] = ++ tot;
        p = Trie[p].Next[c];
    }
    else for ( int i = l; i >= r; -- i ) 
    {
        int c = s[i] - 'a';
        if ( !Trie[p].Next[c] ) Trie[p].Next[c] = ++ tot;
        p = Trie[p].Next[c];
    }
    return p;
}

inline void DFS(int u)
{
    dfn[u] = ++ cnt; size[u] = 1;
    REP(i, 0, 25)
    {
        int v = Trie[u].Next[i]; if ( !v ) continue ;
        DFS(v); size[u] += size[v];
    }
}

inline void DFS1(int u)
{
    for ( auto i : belong[u] ) 
    {
        int x = a[i].first, y = a[i].second; 
        ans += Query(dfn[a[i].second] + size[a[i].second] - 1, 0) - Query(dfn[a[i].second], 0);
        ans += Query(dfn[a[i].second], 1);
        Modify(dfn[a[i].second], 1, 0);
        Modify(dfn[a[i].second], 1, 1); Modify(dfn[a[i].second] + size[a[i].second], -1, 1);
    }
    REP(i, 0, 25) if ( Trie[u].Next[i] ) DFS1(Trie[u].Next[i]);
    for ( auto i : belong[u] ) 
    {
        Modify(dfn[a[i].second], -1, 0);
        Modify(dfn[a[i].second], -1, 1); Modify(dfn[a[i].second] + size[a[i].second], 1, 1);
    }
}

int main()
{
    freopen("chocolate.in", "r", stdin);
    freopen("chocolate.out", "w", stdout);
    tot = 1; REP(i, 0, 25) Trie[0].Next[i] = 1;
    scanf("%d", &n);
    REP(i, 1, n)
    {
        scanf("%s", s + 1); 
        m = 0; while ( s[m + 1] != '#' ) ++ m; a[i].first = Insert(1, m, 1);
        m = str(s + 1) + 1; while ( s[m - 1] != '#' ) -- m; a[i].second = Insert(str(s + 1), m, 0);
    }
    REP(i, 1, n) belong[a[i].first].push_back(i); DFS(1); DFS1(1);
    printf("%lld\n", ans);
    return 0;
}
