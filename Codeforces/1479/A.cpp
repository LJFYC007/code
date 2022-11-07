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

int n;

inline int Get(int x)
{
	if ( x < 1 || x > n ) return n + 1;
	printf("? %d\n", x); fflush(stdout);
	int y; scanf("%d", &y); return y;
}

int main()
{
	scanf("%d", &n);
	int l = 1, r = n;
	while ( l <= r )
	{
		int Mid = l + r >> 1;
		int x = Get(Mid), y = Get(Mid - 1), z = Get(Mid + 1);
		if ( x < min(y, z) ) { printf("! %d\n", Mid); fflush(stdout); return 0; }
		if ( y < x ) r = Mid - 1;
		else l = Mid + 1;
	}
    return 0;
}
