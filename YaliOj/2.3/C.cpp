/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年05月12日 星期日 13时15分44秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 10000010;

struct node
{
	int next[2], v;
} Trie[maxn];

int n, a[maxn], s1[maxn], s2[maxn], tot = 1;
int l[maxn], r[maxn];

inline void INIT(int x)
{
	Trie[x].next[0] = Trie[x].next[1] = Trie[x].v = 0;
}

inline void Insert(int x)
{
	int sum = 1073741824, p = 1, f = x;
	while ( sum ) 
	{
		int c;
		if ( x >= sum ) c = 1; else c = 0;
		if ( x >= sum ) x -= sum; sum /= 2;
		if ( !Trie[p].next[c] ) 
		{
			INIT(++ tot);
			Trie[p].next[c] = tot;
		}
		p = Trie[p].next[c];
	}
	Trie[p].v = f;
}

inline int Search(int x)
{
	int sum = 1073741824, p = 1, f = x;
	while ( sum ) 
	{
		int c;
		if ( x >= sum ) c = 0; else c = 1;
		if ( x >= sum ) x -= sum; sum /= 2;
		if ( !Trie[p].next[c] ) p = Trie[p].next[1 - c];
		else p = Trie[p].next[c];
	}
	return f ^ Trie[p].v;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) scanf("%d", &a[i]); 
	Insert(0);
	REP(i, 1, n) { s1[i] = s1[i - 1] ^ a[i]; Insert(s1[i]); l[i] = max(l[i - 1], Search(s1[i])); }
	mem(Trie); tot = 1;
	Insert(0);
	for ( int i = n; i >= 1; -- i ) 
	{
		s2[i] = s2[i + 1] ^ a[i];
		Insert(s2[i]);
		r[i] = max(r[i + 1], Search(s2[i]));
	}
	int ans = 0;
	REP(i, 1, n - 1) ans = max(ans, l[i] + r[i + 1]);
	printf("%d\n", ans);
//	REP(i, 1, n) printf("%d ", l[i]); puts("");
    return 0;
}
