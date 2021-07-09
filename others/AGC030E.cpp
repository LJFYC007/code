/***************************************************************
	File name: AGC030E.cpp
	Author: ljfcnyali
	Create time: 2021年03月18日 星期四 10时45分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
#define int long long

const int maxn = 5010 * 4;
const int INF = 1e18;

int n, a[maxn], b[maxn], ta[maxn], tb[maxn], n1, n2;
char s[maxn], t[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); scanf("%s", s + 1); scanf("%s", t + 1);
	s[n + 1] = t[n + 1] = '0';
	if ( s[1] == '1' ) ta[++ n1] = 0;
	REP(i, 1, n) if ( s[i] != s[i + 1] ) ta[++ n1] = i;
	if ( t[1] == '1' ) tb[++ n2] = 0;
	REP(i, 1, n) if ( t[i] != t[i + 1] ) tb[++ n2] = i;

	int ret = INF;
	REP(i, 1, n1) a[n2 + i] = ta[i]; REP(i, n1 + n2 + 1, n1 + n2 + n2) a[i] = n;
	for ( int j = 0; j <= n1 + n2; j += 2 ) 
	{
		REP(i, 1, j) b[i] = 0;
		REP(i, 1, n2) b[j + i] = tb[i];
		REP(i, j + n2 + 1, n1 + n2 + n2) b[i] = n;
		int ans = 0; REP(i, 1, n1 + n2 + n2) ans += abs(a[i] - b[i]);
		ret = min(ret, ans);
	}
	printf("%lld\n", ret);
    return 0;
}
