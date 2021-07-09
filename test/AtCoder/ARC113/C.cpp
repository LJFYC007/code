/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年02月21日 星期日 20时33分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 1e9;

int n, num[26], ans;
char s[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%s", s + 1); n = str(s + 1);
	int lst = -1; ++ num[s[n] - 'a'];
	for ( int i = n - 1; i >= 1; -- i ) 
	{
		if ( s[i] == s[i + 1] ) 
		{
			int sum = 0;
			REP(j, 0, 25) if ( j != s[i] - 'a' ) { sum += num[j]; num[j] = 0; } 
			num[s[i] - 'a'] += sum;
			ans += sum;
		}
		++ num[s[i] - 'a'];
	}
	printf("%lld\n", ans);
    return 0;
}
