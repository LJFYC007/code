/***************************************************************
	File name: P3804.cpp
	Author: ljfcnyali
	Create time: 2019年11月24日 星期日 20时46分40秒
***************************************************************/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<map>
#include<stack>
#include<queue>
#include<set>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10;

struct node
{
    int Next[26], len, fa;
} Tree[maxn];
int tot = 1, last = 1, n, Begin[maxn], Next[maxn], To[maxn], e, f[maxn], ans;
char s[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline int NewNode()
{
    int x = ++ tot; 
    REP(i, 0, 25) Tree[x].Next[i] = 0;
    return x;
}

inline void Extand(int c)
{
    int cur = NewNode(); f[cur] = 1;
    Tree[cur].len = Tree[last].len + 1; 
    int p = last; last = cur;
    while ( p && !Tree[p].Next[c] ) { Tree[p].Next[c] = cur; p = Tree[p].fa; }
    if ( !p ) { Tree[cur].fa = 1; return ; }
    int q = Tree[p].Next[c];
    if ( Tree[p].len + 1 == Tree[q].len ) { Tree[cur].fa = q; return ; }
    int clone = NewNode();
    Tree[clone] = Tree[q];
    Tree[clone].len = Tree[p].len + 1;
    while ( p && Tree[p].Next[c] == q ) 
    {
        Tree[p].Next[c] = clone;
        p = Tree[p].fa;
    }
    Tree[q].fa = Tree[cur].fa = clone;
}

inline void DFS(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; DFS(v);
        f[u] += f[v];
    }
    if ( f[u] != 1 ) ans = max(ans, f[u] * Tree[u].len);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s + 1); n = str(s + 1);
    REP(i, 1, n) Extand(s[i] - 'a');
    REP(i, 2, tot) add(Tree[i].fa, i);
    DFS(1);
    printf("%d\n", ans);
    return 0;
}
