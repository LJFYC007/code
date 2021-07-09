/***************************************************************
	File name: CF235C.cpp
	Author: ljfcnyali
	Create time: 2019年11月25日 星期一 21时42分15秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10;

struct node { int Next[26], len, fa; } Tree[maxn];
int n, m, N, last = 1, tot = 1, f[maxn], Begin[maxn], Next[maxn], To[maxn], e;
bool vis[maxn];
char s[maxn];
vector<int> Rub;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Extand(int c)
{
    int cur = ++ tot; f[cur] = 1;
    Tree[cur].len = Tree[last].len + 1;
    int p = last; last = cur; 
    while ( p && !Tree[p].Next[c] ) { Tree[p].Next[c] = cur; p = Tree[p].fa; }
    if ( !p ) { Tree[cur].fa = 1; return ; }
    int q = Tree[p].Next[c];
    if ( Tree[p].len + 1 == Tree[q].len ) Tree[cur].fa = q;
    else
    {
        int clone = ++ tot;
        Tree[clone] = Tree[q]; Tree[clone].len = Tree[p].len + 1;
        while ( p && Tree[p].Next[c] == q ) { Tree[p].Next[c] = clone; p = Tree[p].fa; }
        Tree[cur].fa = Tree[q].fa = clone;
    }
}

inline void DFS(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; DFS(v);
        f[u] += f[v];
    }
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
    scanf("%d", &m); 
    while ( m -- ) 
    {
        scanf("%s", s + 1); N = str(s + 1);
        REP(i, 1, N) s[i + N] = s[i]; N += N;
        int ans = 0, p = 1, len = 0;
        REP(i, 1, N - 1)
        {
            int c = s[i] - 'a';
            while ( p != 1 && !Tree[p].Next[c] ) { p = Tree[p].fa; len = Tree[p].len; }
            if ( Tree[p].Next[c] ) { p = Tree[p].Next[c]; ++ len; }
            while ( p != 1 && Tree[Tree[p].fa].len >= N / 2 ) { p = Tree[p].fa; len = Tree[p].len; }
            if ( len >= N / 2 && !vis[p] ) { ans += f[p]; vis[p] = true; Rub.push_back(p); }
            // if ( len >= N / 2 ) printf("%c %d %d\n", s[i], f[p], len);
        }
        for ( auto i : Rub ) vis[i] = false; Rub.clear();
        printf("%d\n", ans);
    }
    return 0;
}
