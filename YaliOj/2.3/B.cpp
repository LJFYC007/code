/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年05月12日 星期日 11时08分07秒
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

int n, tot, a[maxn], ans;

inline void INIT(int x)
{
	Trie[x].next[0] = Trie[x].next[1] = 0;
	Trie[x].v = -1;
}

inline void Insert(int x)
{
	int sum = 1073741824, p = 1, f = x;
	while ( sum ) 
	{
		int c;
		if ( x >= sum ) c = 1; else c = 0;
		if ( x >= sum ) x -= sum; sum /= 2;
		if ( Trie[p].next[c] == 0 ) 
		{
			++ tot;
			INIT(tot);
			Trie[p].next[c] = tot;
		}
		p = Trie[p].next[c];
	}
	Trie[p].v = f;
}

inline void Find(int x)
{
	int sum = 1073741824, p = 1, f = x;
	while ( sum )
	{
		int c;
		if ( x >= sum ) c = 0; else c = 1;
		if ( x >= sum ) x -= sum; sum /= 2;
		if ( Trie[p].next[c] != 0 ) p = Trie[p].next[c];
		else p = Trie[p].next[1 - c];
	}
//	printf("%d %d\n", f, Trie[p].v);
	if ( f == Trie[p].v ) return ;
	ans = max(ans, f ^ Trie[p].v);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	tot = 1;
	INIT(tot);
	REP(i, 1, n) 
	{
		scanf("%d", &a[i]);
		Insert(a[i]);
	}
	REP(i, 1, n) Find(a[i]);
	printf("%d\n", ans);
    return 0;
}
