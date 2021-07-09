/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年05月13日 星期一 09时50分01秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;
const int maxm = 2000010;

int n, m, tot = 1, ans;
bool f[maxm];
char s[maxm];

struct node
{
	int next[26], finish;
} Trie[maxn];

inline void INIT(int x)
{
	Trie[x].finish = 0;
	REP(i, 0, 25) Trie[x].next[i] = 0;
}

inline void Insert()
{
	int len = str(s), p = 1;
	REP(i, 0, len - 1)
	{
		int c = s[i] - 'a';
		if ( !Trie[p].next[c] ) 
		{
			Trie[p].next[c] = ++ tot;
			INIT(tot);
		}
		p = Trie[p].next[c];
	}
	Trie[p].finish = 1;
}

inline int Search(int u, int t)
{
	int len = str(s), p = 1;
	REP(i, u, t)
	{
		int c = s[i] - 'a';
		if ( !Trie[p].next[c] ) return 0;
		p = Trie[p].next[c];
	}
	return Trie[p].finish;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	INIT(tot);
	scanf("%d%d", &n, &m); getchar();
	int Max = 0;
	REP(i, 1, n)
	{
		scanf("%s", s);
		Max = max(Max, (int)str(s));
		Insert();
	}
	REP(j, 1, m)
	{
		mem(f); scanf("%s", s);
		REP(i, 0, str(s) - 1) 
			REP(k, max(i - Max, -1), i) 
				if ( (k == -1 || f[k] == true) && Search(k + 1, i) )
					f[i] = true;
		bool flag = false;
		for ( int i = str(s) - 1; i >= 0; -- i )
			if ( f[i] == true ) { flag = true; printf("%d\n", i + 1); break ; }
		if ( flag == false ) printf("0\n");
	}
    return 0;
}
