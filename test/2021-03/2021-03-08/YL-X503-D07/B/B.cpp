#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e6 + 10;
const int INF = 0x3f3f3f3f;

int n, m, ans, b[maxn];
char s[maxn], t[maxn];
vector<int> a; vector<pii> Q[maxn];

inline int lowbit(int x) { return x & -x; } 

inline void add(int pos, int val) { for ( int i = pos; i <= n; i += lowbit(i) ) b[i] = max(b[i], val); } 

inline int query(int pos) { int ret = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) ret = max(ret, b[i]); return ret; } 

struct SAM
{
	struct node { int Next[26], fa, len; } Tree[maxn];
	int lst = 1, tot = 1, Endpos[maxn];
	vector<int> Edge[maxn];
	bool vis[maxn];
	
	inline void Extend(int c)
	{
		int cur = ++ tot, p = lst; lst = cur; Tree[cur].len = Tree[p].len + 1; Endpos[cur] = Tree[cur].len;
		while ( p && !Tree[p].Next[c] ) { Tree[p].Next[c] = cur; p = Tree[p].fa; } 
		if ( !p ) { Tree[cur].fa = 1; return ; } 
		int q = Tree[p].Next[c];
		if ( Tree[p].len + 1 == Tree[q].len ) { Tree[cur].fa = q; return ; } 
		int clone = ++ tot; Tree[clone] = Tree[q]; Tree[clone].len = Tree[p].len + 1; Endpos[clone] = INF;
		while ( p && Tree[p].Next[c] == q ) { Tree[p].Next[c] = clone; p = Tree[p].fa; } 
		Tree[q].fa = Tree[cur].fa = clone;
	}

	inline void DFS(int u) { for ( auto v : Edge[u] ) { DFS(v); Endpos[u] = min(Endpos[u], Endpos[v]); } }

	inline void Build()
	{
		REP(i, 1, n) Extend(s[i] - 'a');
		REP(i, 2, tot) Edge[Tree[i].fa].push_back(i);
		DFS(1);
	}

	inline void Solve(int u) { if ( !u || vis[u] ) return ; vis[u] = true; a.push_back(u); Solve(Tree[u].fa); }
} A, B; 

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%s", s + 1); n = str(s + 1);
	scanf("%s", t + 1); m = str(t + 1);
	A.Build(); reverse(s + 1, s + n + 1); B.Build();

	int p = 1, len = 0;
	REP(i, 1, m)
	{
		int c = t[i] - 'a';
		while ( p != 1 && !A.Tree[p].Next[c] ) { p = A.Tree[p].fa; len = A.Tree[p].len; }
		if ( A.Tree[p].Next[c] ) { p = A.Tree[p].Next[c]; ++ len; } 
		a.clear(); A.Solve(A.Tree[p].fa);
		Q[i + 1].push_back(pii(n - A.Endpos[p], len)); ans = max(ans, len);
		for ( auto it : a ) { Q[i + 1].push_back(pii(n - A.Endpos[it], A.Tree[it].len)); ans = max(ans, A.Tree[it].len); }
	}

	p = 1; len = 0;
	for ( int i = m; i >= 1; -- i ) 
	{
		int c = t[i] - 'a';
		while ( p != 1 && !B.Tree[p].Next[c] ) { p = B.Tree[p].fa; len = B.Tree[p].len; } 
		if ( B.Tree[p].Next[c] ) { p = B.Tree[p].Next[c]; ++ len; } 
		a.clear(); B.Solve(B.Tree[p].fa);
		if ( p != 1 ) add(B.Endpos[p], len);
		for ( auto it : a ) if ( it != 1 ) add(B.Endpos[it], B.Tree[it].len);
		for ( auto it : Q[i] ) ans = max(ans, query(it.first) + it.second);
	}

	printf("%d\n", ans);
	return 0;
}
