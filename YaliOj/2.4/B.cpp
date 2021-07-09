/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年05月13日 星期一 13时37分08秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 10000010;

struct node
{
	int next[4];
} Trie[maxn];

int n, m, len[maxn], match[maxn], last[maxn], tot = 1, Next[maxn];
char s[maxn], S[maxn];
bool vis[maxn];

inline int dt(char c)
{
	if ( c == 'E' ) return 0;
	if ( c == 'S' ) return 1;
	if ( c == 'W' ) return 2;
	return 3;
}

inline void Insert(int x)
{
	len[x] = str(s); 
	int p = 1;
	REP(i, 0, len[x] - 1)
	{
		int c = dt(s[i]);
		if ( !Trie[p].next[c] ) Trie[p].next[c] = ++ tot;
		last[Trie[p].next[c]] = p;
		p = Trie[p].next[c];
	}
	match[x] = p;
}

inline void BFS()
{
	REP(i, 0, 3) Trie[0].next[i] = 1;
	queue<int> Q; Q.push(1);
	while ( !Q.empty() ) 
	{
		int u = Q.front(); Q.pop();
		REP(i, 0, 3)
			if ( !Trie[u].next[i] ) Trie[u].next[i] = Trie[Next[u]].next[i];
			else
			{
				Q.push(Trie[u].next[i]);
				Next[Trie[u].next[i]] = Trie[Next[u]].next[i];
			}
	}
}

inline void AC()
{
	int p = 1;
	REP(i, 0, str(S) - 1)
	{
		int c = dt(S[i]);
		p = Trie[p].next[c];
		int v = p;
		while ( v > 1 && !vis[v] ) { vis[v] = true; v = Next[v]; }
	}
}

inline void Solve(int x)
{
	int p = match[x];;
	while ( len[x] && p > 1 ) 
	{
		if ( vis[p] ) { printf("%d\n", len[x]); return ; }
		p = last[p];
		-- len[x];
	}
	printf("0\n");
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	scanf("%s", S); mem(Trie);
	REP(i, 1, m)
	{
		scanf("%s", s);
		Insert(i);
	}
	BFS();
	AC();
	REP(i, 1, m) Solve(i);
    return 0;
}
