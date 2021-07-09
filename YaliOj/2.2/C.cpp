/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年05月12日 星期日 09时00分54秒
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
	scanf("%d", &n); getchar();
	scanf("%s", s);
	int j = 0;
	REP(i, 1, n - 1)
	{
		while ( j && s[i] != s[j] ) j = Next[j];
		Next[i + 1] = s[i] == s[j] ? ++ j : 0;
	}
	printf("%d\n", n - Next[n]);
    return 0;
}
