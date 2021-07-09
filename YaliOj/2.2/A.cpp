/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年05月12日 星期日 08时39分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

char s1[1000010], s2[1000010];
int Next[1000010], n, m, ans;

inline void Solve()
{
	ans = 0;
	int j = 0;
	REP(i, 1, m - 1)
	{
		while ( j && s2[i] != s2[j] ) j = Next[j];
		Next[i + 1] = s2[i] == s2[j] ? ++ j : 0;
	}
	j = 0;
	REP(i, 0, n - 1)
	{
		while ( j && s1[i] != s2[j] ) j = Next[j];
		if ( s1[i] == s2[j] ) ++ j;
		if ( j == m ) { ++ ans; j = 0; }
	}
	printf("%d\n", ans);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	while ( 1 ) 
	{
		scanf("%s ", s1); n = str(s1);
		if ( n == 1 && s1[0] == '#' ) return 0;
		scanf("%s ", s2); m = str(s2);
//		printf("%s %s\n", s1, s2);
		mem(Next); Solve();
	}
    return 0;
}
