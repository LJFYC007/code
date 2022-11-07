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
	int n; cin >> n;
	while ( n -- )
	{
		LL c, sum; cin >> c >> sum;
		LL x = sum / c, ret = 0;
		REP(i, 1, sum - x * c) ret += (x + 1) * (x + 1);
		REP(i, sum - x * c + 1, c) ret += x * x;
		cout << ret << endl;
	}
	return 0;
}
