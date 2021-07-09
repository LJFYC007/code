#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;
 
const int maxn = 1010;
 
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while ( T -- )
	{
		int a, b; scanf("%d%d", &a, &b);
		int x = 2 * b - a;
		if ( x % 3 == 0 && x >= 0 && a >= x / 3 ) puts("YES");
		else puts("NO");
	}
	return 0;
}
