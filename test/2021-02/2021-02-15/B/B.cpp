/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年02月16日 星期二 10时24分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 4e6 + 10;

int n, ans, g[maxn], Begin[maxn], Next[maxn], To[maxn], e, Max, r[maxn];
struct SAM
{
	struct node { int Next[2], len, fa; } Tree[maxn];
	int tot = 1, last = 1, sum;
	bool vis[maxn];

	inline int NewNode()
	{
		int x = ++ tot; Tree[x].Next[0] = Tree[x].Next[1] = Tree[x].len = Tree[x].fa = 0;
		return x;
	}

	inline void INIT() { tot = 0; last = 1; sum = 0; NewNode(); }

	inline void Extand(int c)
	{
		int cur = NewNode(), p = last; Tree[cur].len = Tree[p].len + 1; last = cur; 
		while ( p && !Tree[p].Next[c] ) { Tree[p].Next[c] = cur; p = Tree[p].fa; } 	
		if ( !p ) { Tree[cur].fa = 1; sum += Tree[cur].len; return ; } 
		int q = Tree[p].Next[c];
		if ( Tree[p].len + 1 == Tree[q].len ) { Tree[cur].fa = q; sum += Tree[cur].len - Tree[q].len; return ; } 
		int clone = NewNode(); Tree[clone] = Tree[q]; Tree[clone].len = Tree[p].len + 1; r[clone] = r[q];
		while ( p && Tree[p].Next[c] == q ) { Tree[p].Next[c] = clone; p = Tree[p].fa; } 
		Tree[q].fa = Tree[cur].fa = clone; sum += Tree[cur].len - Tree[clone].len;
	}
} A, B;
char s[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS(int u, int dep)
{
	if ( dep && A.vis[u] ) { Max = max(Max, dep); g[dep] += A.Tree[u].len - A.Tree[A.Tree[u].fa].len; return ; }
	for ( int i = Begin[u]; i; i = Next[i] ) DFS(To[i], dep + 1);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%s", s + 1); n = str(s + 1);
	REP(i, 1, n) { A.Extand(s[i] - '0'); r[A.last] = i; }
	for ( int i = A.tot; i >= 1; -- i ) REP(c, 0, 1) if ( A.Tree[i].Next[c] ) add(A.Tree[i].Next[c], i);

	int x = A.last; while ( x ) { A.vis[x] = true; x = A.Tree[x].fa; } 			
	REP(i, 1, A.tot) if ( A.Tree[i].Next[0] && A.Tree[i].Next[1] ) A.vis[i] = true;
	A.Tree[0].len = -1;
	REP(i, 1, A.tot) if ( A.vis[i] )
	{ 
		Max = 0; DFS(i, 0); B.INIT();
		REP(j, 1, Max) { B.Extand(s[r[i] - j + 1] - '0'); ans += g[j] * B.sum; g[j] = 0; }
	}
	printf("%lld\n", ans);
    return 0;
}
