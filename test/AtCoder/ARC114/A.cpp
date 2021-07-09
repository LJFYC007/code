/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年03月16日 星期二 19时54分04秒
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
const int INF = 9e18;

int n, a[maxn], f[maxn] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47}, ans = INF;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n) scanf("%lld", &a[i]);
	REP(i, 1, (1 << 15) - 1)
	{
		int ret = 1;
		REP(j, 1, 15) if ((i >> j - 1) & 1 ) ret *= f[j];
		bool flag = true;
		REP(j, 1, n) if ( __gcd(ret, a[j]) == 1 ) flag = false;
		if ( flag ) ans = min(ans, ret);
	}
	printf("%lld\n", ans);
    return 0;
}
