/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年05月12日 星期日 10时47分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

struct node
{
	int Next[20], finish;
} Trie[1000010];

int n, tot, len;
char s[20];
bool flag, Flag;

inline void Delete(int x)
{
	Trie[x].finish = 0;
	REP(i, 0, 18) Trie[x].Next[i] = -1;
}

inline void Insert()
{
	int p = 1;
	len = str(s);
	REP(i, 0, len - 1)
	{
		int c = s[i] - '0';
		if ( Trie[p].Next[c] == -1 )
		{
			Trie[p].Next[c] = ++ tot;
			Delete(tot);
		}
		p = Trie[p].Next[c];
		if ( Trie[p].finish == 2 ) Flag = true;
		if ( Trie[p].finish == 1 ) flag = true;
		else flag = false;
		Trie[p].finish = 1;
	}
	Trie[p].finish = 2;
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
		tot = 1; Delete(tot);
		scanf("%d", &n); getchar();
		Flag = false;
		REP(i, 1, n)
		{
			scanf("%s", s);
			flag = false;
			Insert();
			if ( flag == true ) Flag = true;
		}
		if ( Flag == true ) printf("NO\n");
		else printf("YES\n");
	}
    return 0;
}
