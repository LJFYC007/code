/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年02月23日 星期二 16时59分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;

int T, p, a, b, c;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	cin >> T;
	while ( T -- ) 
	{
		cin >> p >> a >> b >> c;
		int ans = min(((p - 1) / a + 1) * a - p, ((p - 1) / b + 1) * b - p);
		ans = min(ans, (((p - 1) / c + 1) * c - p));
		cout << ans << endl;
	}
    return 0;
}
