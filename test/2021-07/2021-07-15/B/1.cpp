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
typedef long long LL;

const int maxn = 1e6 + 10;

int n, tot = 1, lst = 1, ans, dfn[maxn], cnt, Len[maxn];
int Max[maxn], Min[maxn], son[maxn];
struct NODE { int len, fa, Next[26]; } Trie[maxn];
set<int> Set[maxn];
// struct node { int lson, rson, sum; 
char s[maxn]; bool vis[maxn];
vector<int> Edge[maxn]; 

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
		DFS(v); Max[u] = max(Max[u], Max[v]); Min[u] = min(Min[u], Min[v]);
		for ( auto it : Set[v] ) Set[u].insert(it);
		// Merge(Root[u], Root[v]);
	}
	for ( auto v : Edge[u] ) if ( Max[u] == Max[v] ) son[u] = v;
}

inline int Check(int x, int y)
{
	vector<int> a; for ( auto it : Set[x] ) a.push_back(it);
	vector<int> b; for ( auto it : Set[y] ) b.push_back(it);
	while ( !a.empty() ) 
	{
		if ( a.back() != b.back() ) return -1;
		a.pop_back(); b.pop_back();
	}
	return b.back();
}

inline void Solve(int u, int t, int sum)
{
	if ( !u ) return ; vis[u] = true;
	int fa = Trie[u].fa, pos = Check(u, t);
	if  ( pos != -1 ) 
	{
		if ( pos <= Trie[u].len ) ans += sum * (Trie[u].len - pos);
		while ( fa != t ) 
		{
			int x = Check(u, fa);
			if ( x <= Trie[u].len ) ans += Len[fa] * (Trie[u].len - x);
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
	REP(i, 1, n) { Set[tot + 1].insert(i); Max[tot + 1] = Min[tot + 1] = i; Extend(s[i] - 'a'); }
	REP(i, 2, tot) Edge[Trie[i].fa].push_back(i);
	tot = 0; DFS(1);
	REP(i, 2, tot) 
	{
		Len[i] = Trie[i].len - Trie[Trie[i].fa].len;
		ans += Len[i] * (Len[i] - 1) / 2; 
	}
	REP(i, 2, tot)
	{
		int u = dfn[i]; if ( vis[u] ) continue ; 
		Solve(son[u], u, Len[u]);
	}
	printf("%d\n", ans);
    return 0;
} 
