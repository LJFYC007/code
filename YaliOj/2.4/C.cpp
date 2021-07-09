/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年05月13日 星期一 15时01分44秒
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

int Next[maxn], n, tot = 1, ans[maxn], Max, last[maxn];
char S[maxn], s[maxn];

inline void Insert()
{
	int len = str(s), p = 1; Max = max(Max, len);
	REP(i, 0, len - 1)
	{
		int c = s[i] - 'a';
		if ( !Trie[p].next[c] ) Trie[p].next[c] = ++ tot;
		p = Trie[p].next[c];
	}
	Trie[p].val = len;
}

inline void BFS()
{
	queue<int> Q; Q.push(1);
	REP(i, 0, 25) Trie[0].next[i] = 1;
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
	int len = str(S), p = 1, sum = 0;
	for ( int i = 0; i < len; ++ i )
	{
		int c = S[i] - 'a'; ans[++ sum] = S[i];
		p = Trie[p].next[c];
		last[sum] = p;
		if ( Trie[p].val ) 
		{
			sum -= Trie[p].val;
			p = last[sum];
		}
	}
	REP(i, 1, sum) printf("%c", ans[i]);
	puts("");
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%s", S); scanf("%d", &n); getchar();
	mem(Trie);
	REP(i, 1, n)
	{
		scanf("%s", s);
		Insert();
	}
	BFS();
	AC();
    return 0;
}
