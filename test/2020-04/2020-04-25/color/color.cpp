#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1010;

signed main()
{
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	int T; scanf("%lld", &T);
	while ( T -- )
	{
		int a, b, k; cin >> a >> b >> k;
		if ( a > b ) swap(a, b);
		int x = __gcd(a, b);
		if ( (b - 1 - x) / a < k - 1 ) cout << "Yes" << endl;
		else cout << "No"<< endl;
	}
	return 0;
}
