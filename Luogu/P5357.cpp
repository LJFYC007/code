/***************************************************************
	File name: P3808.cpp
	Author: ljfcnyali
	Create time: 2019年05月12日 星期日 14时56分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 5000010;

struct node
{
	int next[26];
//	bool flag;
//	queue<int> val;
} Trie[maxn];

int Next[maxn], n, len, tot, match[maxn], num[maxn];
int Fail[maxn], To[maxn], Begin[maxn], e;
char s[maxn];

inline void INIT(int x)
{
	REP(i, 0, 25) Trie[x].next[i] = 0;
//	Trie[x].flag = false;
}

inline void Insert(int x)
{
	len = str(s);
	int p = 1;
	REP(i, 0, len - 1)
	{
		int c = s[i] - 'a';
		if ( Trie[p].next[c] == 0 )
		{
			Trie[p].next[c] = ++ tot;
			INIT(tot);
		}
		p = Trie[p].next[c];
	}
	match[x] = p;
//	Trie[p].flag = true;
//	Trie[p].val.push(x);
}

inline void BFS()
{
	queue<int> Q;
	Q.push(1);
	while ( !Q.empty() )
	{
		int u = Q.front(); Q.pop();
		REP(i, 0, 25)
		{
			if ( Trie[u].next[i] == 0 ) { Trie[u].next[i] = Trie[Fail[u]].next[i]; continue; }
			Q.push(Trie[u].next[i]);
			Fail[Trie[u].next[i]] = Trie[Fail[u]].next[i];
		}
	}
}

inline void add(int u, int v)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
}

inline void DFS(int u)
{
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i];
		DFS(v);
		num[u] += num[v];
	}
}

inline void AC()
{
	int u = 1; len = str(s);
	REP(i, 0, len - 1)
	{
		int c = s[i] - 'a';
		u = Trie[u].next[c];
		++ num[u];
	}
	REP(i, 2, tot) add(Fail[i], i);
	DFS(1);
	REP(i, 1, n) printf("%d\n", num[match[i]]);
}

/* inline void AC()
{
	int u = 1; len = str(s);
	REP(i, 0, len - 1)
	{
		int c = s[i] - 'a';
		int v = Trie[u].next[c];
		while ( v > 1 && Trie[v].flag == true ) 
		{
			Trie[v].flag = false;
			while ( !Trie[v].val.empty() ) 
			{
				ans[Trie[v].val.front()] ++;
				Trie[v].val.pop();
			}
			v = Next[v];
		}
		u = Trie[u].next[c]; 
	}
}
*/

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); getchar();
	REP(i, 0, 25) Trie[0].next[i] = 1; // Trie[0].flag = false;
	tot = 1; INIT(tot);
	REP(i, 1, n)
	{
		scanf("%s", s);
		Insert(i);
	}
	BFS();
	scanf("%s", s);
	AC();
    return 0;
}
