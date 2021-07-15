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

const int maxn = 1e5 + 10;

int n, tot = 1, lst = 1, ans;
struct NODE { int len, fa, Next[26]; } Trie[maxn];
char s[maxn]; set<int> Set[maxn]; vector<int> Edge[maxn];

inline void Extend(int c)
{
	int p = lst, cur = ++ tot; Trie[cur].len = Trie[p].len + 1; lst = cur;
	while ( p && !Trie[p].Next[c] ) { Trie[p].Next[c] = cur; p = Trie[p].fa; } 
	if ( !p ) { Trie[cur].fa = 1; return ; } 
	int q = Trie[p].Next[c];
	if ( Trie[p].len + 1 == Trie[q].len ) { Trie[cur].fa = q; return ; } 
	int clone = ++ tot; Trie[clone] = Trie[q]; Trie[clone].len = Trie[p].len + 1;
	while ( p && Trie[p].Next[c] == q ) { Trie[p].Next[c] = clone; p = Trie[p].fa; } 
	Trie[q].fa = Trie[cur].fa = clone;
}

inline void DFS(int u)
{
	int sum = Set[u].size();
	for ( auto v : Edge[u] ) 
	{
		DFS(v); sum += Set[v].size();
		for ( auto it : Set[v] ) 
			Set[u].insert(it);
	}
	assert(sum == Set[u].size());
}

inline void Solve(int x, int y)
{
	if ( y == 1 ) return ; 
	int pos = 0;
	vector<int> a; for ( auto it : Set[x] ) a.push_back(it);
	vector<int> b; for ( auto it : Set[y] ) b.push_back(it);
	while ( !a.empty() ) 
	{
		if ( a.back() != b.back() ) return ;
		a.pop_back(); b.pop_back();
	}
	pos = b.back();
	// cerr << x << " " << y << " " << pos << endl;
	if ( pos >= Trie[x].len ) return ;
	ans += (Trie[y].len - Trie[Trie[y].fa].len) * (Trie[x].len - pos);
	Solve(x, Trie[y].fa);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); 
	scanf("%s", s + 1); reverse(s + 1, s + n + 1);
	REP(i, 1, n) { Set[tot + 1].insert(i); Extend(s[i] - 'a'); }
	REP(i, 2, tot) Edge[Trie[i].fa].push_back(i);
	DFS(1);
	REP(i, 2, tot) 
	{
		int len = Trie[i].len - Trie[Trie[i].fa].len;
		ans += len * (len - 1) / 2;
		Solve(i, Trie[i].fa);
	}
	printf("%d\n", ans);
    return 0;
}
