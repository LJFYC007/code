/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年05月12日 星期日 08时55分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;

char s[maxn];
int Next[maxn], n;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	while ( 1 ) 
	{
		scanf("%s", s); n = str(s);
		if ( n == 1 && s[0] == '.' ) return 0;
		int j = 0;
		REP(i, 1, n - 1)
		{
			while ( j && s[i] != s[j] ) j = Next[j];
			Next[i + 1] = s[i] == s[j] ? ++ j : 0;
		}
		if ( n % (n - Next[n]) == 0 ) printf("%d\n", n / (n - Next[n]));
		else printf("1\n");
	}
    return 0;
}
