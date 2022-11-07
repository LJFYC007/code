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

int n, q, a[maxn], sum;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &q);
	REP(i, 1, n) { scanf("%d", &a[i]); sum += a[i]; } 
	while ( q -- ) 
	{
		int op, x; scanf("%d%d", &op, &x);
		if ( op == 1 ) { sum -= a[x]; a[x] ^= 1; sum += a[x]; } 
		else printf("%d\n", sum >= x ? 1 : 0);
	}
    return 0;
}
