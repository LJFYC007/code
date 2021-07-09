/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年05月13日 星期一 11时32分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 2000010;

struct node
{
	int next[26], val;
} Trie[maxn];

int n, m, Next[maxn], tot = 1, ans;
char s[maxn];

inline void Insert()
{
	int len = str(s), p = 1;
	REP(i, 0, len - 1)
	{
		int c = s[i] - 'a';
		if ( !Trie[p].next[c] ) Trie[p].next[c] = ++ tot;
		p = Trie[p].next[c];
	}
	Trie[p].val ++;
}

inline void BFS()
{
	queue<int> Q; Q.push(1);
	while ( !Q.empty() )
	{
		int u = Q.front(); Q.pop();
		REP(i, 0, 25)
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
	int len = str(s), p = 1;
	REP(i, 0, len - 1)
	{
		int c = s[i] - 'a';
		int v = Trie[p].next[c];
		while ( v > 1 )
		{
			ans += Trie[v].val; Trie[v].val = 0;
			v = Next[v];
		}
		p = Trie[p].next[c];
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while ( T -- )
	{
		mem(Trie); mem(Next); tot = 1;
		scanf("%d", &n); getchar();
		REP(i, 1, n)
		{
			scanf("%s", s);	
			Insert();
		}
		BFS();
		scanf("%s", s);
		ans = 0;
		AC();
		printf("%d\n", ans);
	}
    return 0;
}
