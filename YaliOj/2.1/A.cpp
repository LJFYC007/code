/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年05月10日 星期五 15时49分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 2000010;

char s1[maxn], s2[maxn];
int n, m, Next[maxn], ans;

inline void Solve()
{
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
		if ( j == m ) ++ ans;
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%s", s1); n = str(s1);
	getchar();
	scanf("%s", s2); m = str(s2);
	Solve();	
	printf("%d\n", ans);
    return 0;
}
