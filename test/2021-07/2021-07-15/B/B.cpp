/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年07月15日 星期四 10时14分31秒
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

int n, tot = 1, lst = 1, dfn[maxn], cnt, Len[maxn]; LL ans;
int Max[maxn], Min[maxn], son[maxn], Root[maxn], a[maxn];
struct NODE { int len, fa, Next[26]; } Trie[maxn];
struct node { int lson, rson, num; } Tree[maxn << 4];
char s[maxn]; bool vis[maxn];
vector<int> Edge[maxn]; 

inline void Modify(int &root, int l, int r, int pos)
{
	if ( !root ) root = ++ cnt; ++ Tree[root].num;
	if ( l == r ) return ;
	int Mid = l + r >> 1;
	if ( pos <= Mid ) Modify(ls(root), l, Mid, pos);
	else Modify(rs(root), Mid + 1, r, pos);
}

inline int Merge(int p, int q, int l, int r)
{
	if ( !p || !q ) return p + q;
	int root = ++ cnt, Mid = l + r >> 1;
	ls(root) = Merge(ls(p), ls(q), l, Mid);
	rs(root) = Merge(rs(p), rs(q), Mid + 1, r);
	Tree[root].num = Tree[ls(root)].num + Tree[rs(root)].num;
	return root;
}

inline int Query(int root, int l, int r, int L, int R)
{
	if ( !root ) return 0; 
	if ( L <= l && r <= R ) return Tree[root].num;
	int Mid = l + r >> 1, ret = 0;
	if ( L <= Mid ) ret += Query(ls(root), l, Mid, L, R);
	if ( Mid < R ) ret += Query(rs(root), Mid + 1, r, L, R);
	return ret;
}

inline int Find(int root, int l, int r, int L, int R)
{
	if ( !Tree[root].num ) return -1;
	if ( l == r ) return l;
	int Mid = l + r >> 1;
	if ( Mid < R ) { int x = Find(rs(root), Mid + 1, r, L, R); if ( x != -1 ) return x; } 
	if ( L <= Mid ) return Find(ls(root), l, Mid, L, R);
	return -1;
}

inline void Extend(int c)
{
	int p = lst, cur = ++ tot; Trie[cur].len = Trie[p].len + 1; lst = cur;
	while ( p && !Trie[p].Next[c] ) { Trie[p].Next[c] = cur; p = Trie[p].fa; } 
	if ( !p ) { Trie[cur].fa = 1; return ; } 
	int q = Trie[p].Next[c];
	if ( Trie[p].len + 1 == Trie[q].len ) { Trie[cur].fa = q; return ; } 
	int clone = ++ tot; Min[clone] = n + 1; Trie[clone] = Trie[q]; Trie[clone].len = Trie[p].len + 1;
	while ( p && Trie[p].Next[c] == q ) { Trie[p].Next[c] = clone; p = Trie[p].fa; } 
	Trie[q].fa = Trie[cur].fa = clone;
}

inline void DFS(int u)
{
	dfn[++ tot] = u;
	for ( auto v : Edge[u] ) 
	{
		DFS(v); Max[u] = max(Max[u], Max[v]); Min[u] = min(Min[u], Min[v]); a[u] += a[v];
		Root[u] = Merge(Root[u], Root[v], 1, n);
	}
	for ( auto v : Edge[u] ) if ( Max[u] == Max[v] ) son[u] = v;
}

inline int Check(int x, int y)
{
	if ( Query(Root[y], 1, n, Min[x], n) != a[x] ) return -1;
	return Find(Root[y], 1, n, 1, Min[x] - 1);
}

inline void Solve(int u, int t, LL sum)
{
	if ( !u ) return ; vis[u] = true;
	int fa = Trie[u].fa, pos = Check(u, t);
	if  ( pos != -1 ) 
	{
		if ( pos <= Trie[u].len ) ans += sum * (Trie[u].len - pos);
		while ( fa != t ) 
		{
			int x = Check(u, fa);
			if ( x <= Trie[u].len ) ans += 1ll * Len[fa] * (Trie[u].len - x);
			sum += Len[fa]; fa = Trie[fa].fa; 
		}
		sum += Len[u]; Solve(son[u], u, sum);
	}
	else Solve(son[u], t, sum);	
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); 
	scanf("%s", s + 1); reverse(s + 1, s + n + 1);
	REP(i, 1, n) 
	{ 
		Modify(Root[tot + 1], 1, n, i); a[tot + 1] = 1;
		Max[tot + 1] = Min[tot + 1] = i; Extend(s[i] - 'a'); 
	}
	REP(i, 2, tot) Edge[Trie[i].fa].push_back(i);
	tot = 0; DFS(1);
	REP(i, 2, tot) 
	{
		Len[i] = Trie[i].len - Trie[Trie[i].fa].len;
		ans += 1ll * Len[i] * (Len[i] - 1) / 2; 
	}
	REP(i, 2, tot)
	{
		int u = dfn[i]; if ( vis[u] ) continue ; 
		Solve(son[u], u, Len[u]);
	}
	printf("%lld\n", ans);
    return 0;
} 
