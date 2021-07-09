/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年05月12日 星期日 09时29分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;

char a[maxn], s[maxn];
int n, len, Next[maxn], p, ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%s", s); scanf("%d", &p); n = str(s);
	REP(i, 0, n - 1)
	{
		mem(Next); len = 0;
		REP(j, i, n - 1) a[len ++] = s[j];
		int j = 0;
		REP(k, 1, len - 1)
		{
			while ( j && a[k] != a[j] ) j = Next[j];
			Next[k + 1] = a[k] == a[j] ? ++ j : 0;
			for ( int o = Next[k + 1]; o >= p; o = Next[o] )
				if ( (o << 1) <= k ) { ++ ans; break ; }
		}
	}
	printf("%d\n", ans);
    return 0;
}
