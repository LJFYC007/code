/***************************************************************
	File name: AGC037C.cpp
	Author: ljfcnyali
	Create time: 2021年02月04日 星期四 10时30分38秒
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

int n, a[maxn], b[maxn];
set<pii> Set;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n) scanf("%lld", &a[i]);
	REP(i, 1, n) { scanf("%lld", &b[i]); Set.insert(pii(b[i], i)); }
	int ans = 0;
	while ( !Set.empty() ) 
	{
		auto it = -- Set.end();
		int x = (*it).second; Set.erase(it);
		if ( b[x] < a[x] ) { puts("-1"); return 0; } 
		if ( b[x] == a[x] ) continue ;
		int pre = x == 1 ? n : x - 1, suf = x == n ? 1 : x + 1;
		if ( b[pre] + b[suf] > b[x] ) { puts("-1"); return 0; }
		int val = (b[x] - a[x]) / (b[pre] + b[suf]);
		if ( !val ) { puts("-1"); return 0; } 
		ans += val;
		b[x] -= val * (b[pre] + b[suf]);
		Set.insert(pii(b[x], x));
	}
	printf("%lld\n", ans);
    return 0;
}
