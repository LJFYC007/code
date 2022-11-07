/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int q;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &q);
	while ( q -- ) 
	{
		int u, v, val1 = 0, val2 = 0; scanf("%d%d", &u, &v);
		if ( u > v ) { puts("NO"); goto Next; } 
		REP(i, 0, 30) 
		{
			if ( (u >> i) & 1 ) ++ val1;
			if ( (v >> i) & 1 ) ++ val2;
			if ( val1 < val2 ) { puts("NO"); goto Next; } 
		}
		puts("YES");
Next : ;
	}
    return 0;
}
