/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年03月28日 星期日 09时07分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 1e5 + 10;
const int INF = 1e18;

int n, a[maxn], b[maxn];

inline int Check(int x)
{
	int sum = 0;
	REP(i, 1, n) sum += abs(a[i] - (b[i] ^ x));
	return sum;
}

inline pii DFS(int x, int m)
{
	if ( m == -1 ) return pii(Check(x), 1);
	int sum1 = Check(x), sum2 = Check(x ^ (1ll << m));
	if ( sum1 < sum2 ) return DFS(x, m - 1);
	if ( sum1 > sum2 ) return DFS(x ^ (1ll << m), m - 1);
	pii ans1 = DFS(x, m - 1), ans2 = DFS(x ^ (1ll << m), m - 1);
	if ( ans1.first < ans2.first ) return ans1;
	if ( ans1.first > ans2.first ) return ans2;
	return pii(ans1.first, ans1.second + ans2.second);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n) scanf("%lld", &a[i]);
	REP(i, 1, n) scanf("%lld", &b[i]);
	pii ans = DFS(0, 47);
	printf("%lld %lld\n", ans.first, ans.second);
    return 0;
}
