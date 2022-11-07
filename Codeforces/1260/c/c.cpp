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
		LL a, b, k; cin >> a >> b >> k;
		if ( a > b ) swap(a, b);
		int x = __gcd(a, b);
		if ( (b - 1 - x) / a < k ) cout << "OBEY" << endl;
		else puts("REBEL");
	}
	return 0;
}
