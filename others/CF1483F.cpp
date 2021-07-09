/***************************************************************
	File name: CF1483F.cpp
	Author: ljfcnyali
	Create time: 2021年03月30日 星期二 21时56分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, tot = 1, Fail[maxn], dfn[maxn], size[maxn], cnt, tran[maxn], c[maxn], w[maxn], t[maxn], len[maxn];
string s[maxn]; vector<int> Edge[maxn];
struct node { int Next[26], pos; } Tree[maxn];
LL ans;

inline int lowbit(int x) { return x & -x; } 
inline void add(int pos, int val) { for ( int i = pos; i <= cnt; i += lowbit(i) ) c[i] += val; } 
inline int query(int pos) { int ret = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) ret += c[i]; return ret; } 

inline void DFS(int u, int fa)
{
	dfn[u] = ++ cnt; size[u] = 1; tran[u] = Tree[u].pos ? Tree[u].pos : tran[fa];
	for ( auto v : Edge[u] ) { DFS(v, u); size[u] += size[v]; }
}

inline void Build()
{
	queue<int> Q; Q.push(1);
	while ( !Q.empty() ) 
	{
		int u = Q.front(); Q.pop();
		REP(i, 0, 25) 
		{
			if ( !Tree[u].Next[i] ) { Tree[u].Next[i] = Tree[Fail[u]].Next[i]; continue ; } 
			Fail[Tree[u].Next[i]] = Tree[Fail[u]].Next[i]; Q.push(Tree[u].Next[i]);
		}
	}
	REP(i, 2, tot) Edge[Fail[i]].push_back(i); DFS(1, 0);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); REP(i, 0, 25) Tree[0].Next[i] = 1;
	REP(i, 1, n)
	{
		cin >> s[i]; int p = 1; len[i] = s[i].length();
		for ( auto it : s[i] ) { int c = it - 'a'; if ( !Tree[p].Next[c] ) Tree[p].Next[c] = ++ tot; p = Tree[p].Next[c]; }
		Tree[p].pos = i; t[i] = p;
	}
	Build();
	REP(i, 1, n)
	{
		vector<int> a; int Min = s[i].length(); set<int> Set;
		int p = 1; for ( auto it : s[i] ) { p = Tree[p].Next[it - 'a']; add(dfn[p], 1); a.push_back(tran[p]); }
		a.back() = tran[Fail[p]];
		for ( int j = a.size() - 1; j >= 0; -- j ) if ( a[j] ) 
		{
			int x = a[j]; Set.insert(x);
			if ( j - len[x] < Min ) { Min = j - len[x]; ++ w[x]; } 
		}
		for ( auto it : Set ) 
		{
			if ( w[it] == query(dfn[t[it]] + size[t[it]] - 1) - query(dfn[t[it]] - 1) ) ++ ans;
			w[it] = 0;
		}
		p = 1; for ( auto it : s[i] ) { p = Tree[p].Next[it - 'a']; add(dfn[p], -1); }
	}
	printf("%lld\n", ans);
    return 0;
}
