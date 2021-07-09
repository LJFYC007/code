/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2019年05月13日 星期一 10时28分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 50000010;

struct node
{
	int next[2], val, sum;
} Trie[maxn];

int tot = 1, n, m, ans, a[maxn], num;

inline void INIT(int x)
{
	Trie[x].next[0] = Trie[x].next[1] = Trie[x].val = Trie[x].sum = 0;
}

inline void Push_up(int x)
{
	if ( Trie[x].next[0] ) Push_up(Trie[x].next[0]);
	if ( Trie[x].next[1] ) Push_up(Trie[x].next[1]);
	Trie[x].sum = Trie[x].val;
	Trie[x].sum += Trie[Trie[x].next[0]].sum + Trie[Trie[x].next[1]].sum;
}

inline void Insert()
{
	int p = 1;
	REP(i, 1, num)
	{
		if ( !Trie[p].next[a[i]] ) 
		{
			Trie[p].next[a[i]] = ++ tot;
			INIT(tot);
		}
		p = Trie[p].next[a[i]];
	}
	Trie[p].val ++; 
}

inline void Search()
{
	int p = 1;
	REP(i, 1, num)
	{
		if ( !Trie[p].next[a[i]] ) return ;
		p = Trie[p].next[a[i]];
		ans += Trie[p].val;
	}
	ans -= Trie[p].val;
	ans += Trie[p].sum;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	INIT(tot);
	REP(i, 1, n)
	{
		scanf("%d", &num);
		REP(j, 1, num) scanf("%d", &a[j]);
		Insert();
	}
	Push_up(1);
	REP(i, 1, m)
	{
		scanf("%d", &num); ans = 0;
		REP(j, 1, num) scanf("%d", &a[j]);
		Search();
		printf("%d\n", ans);
	}
    return 0;
}
