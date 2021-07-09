/***************************************************************
	File name: P4248.cpp
	Author: ljfcnyali
	Create time: 2019年12月17日 星期二 09时20分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;

int n, last = 1, tot = 1, size[maxn], Begin[maxn], Next[maxn], To[maxn], e, d[maxn], a[maxn], cnt;
LL ans, ret;
queue<int> Q;
struct node { int Next[26], fa, len; } Tree[maxn];
char s[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Insert(int c)
{
    int cur = ++ tot; Tree[cur].len = Tree[last].len + 1; size[cur] = 1;
    int p = last; last = cur;
    while ( p && !Tree[p].Next[c] ) { Tree[p].Next[c] = cur; p = Tree[p].fa; }
    if ( !p ) { Tree[cur].fa = 1; return ; }
    int q = Tree[p].Next[c];
    if ( Tree[p].len + 1 == Tree[q].len ) { Tree[cur].fa = q; return ; }
    int clone = ++ tot;
    Tree[clone] = Tree[q]; Tree[clone].len = Tree[p].len + 1;
    while ( p && Tree[p].Next[c] == q ) { Tree[p].Next[c] = clone; p = Tree[p].fa; }
    Tree[cur].fa = Tree[q].fa = clone;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s + 1); n = str(s + 1);
    REP(i, 1, n) Insert(s[i] - 'a');
    REP(i, 2, tot) { add(Tree[i].fa, i); ++ d[Tree[i].fa]; }
    REP(i, 1, tot) if ( !d[i] ) Q.push(i);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        a[++ cnt] = u;
        int v = Tree[u].fa; -- d[v];
        if ( !d[v] ) Q.push(v);
    }
    ans = n * (n - 1) * (n + 1) / 2;
    REP(i, 1, cnt)
    {
        int f = Tree[a[i]].fa;
        ret += size[a[i]] * size[f] * Tree[f].len;
        size[f] += size[a[i]];
    }
    ans -= 2 * ret;
    printf("%lld\n", ans);
    return 0;
}
