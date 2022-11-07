/***************************************************************
	File name: HaHa
	Author: ljfcnyali
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
const int INF = 1e18;

int K, n, m, a[maxn], b[maxn];
pii p[maxn];

inline bool Check(int x)
{
	int sum = 0;
	REP(i, 1, K)
	{
		int r = x + a[i] * m, l = a[i] * m - x;
		l = max(l, 0ll);
		p[i] = pii((l + n - 1) / n, r / n);
		p[i].first = max(p[i].first , 0ll);
		if ( p[i].first > p[i].second ) return false;
		sum += p[i].first; b[i] = p[i].first;
	}
	if ( sum > m ) return false;
	int i = K;
	while ( sum <= m && i >= 1 )
	{
		int val = min(p[i].second - p[i].first, m - sum);
		sum += val; b[i] += val;
		if ( sum == m ) return true;
		-- i;
	}
	return false;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld", &K, &n, &m);
	REP(i, 1, K) scanf("%lld", &a[i]);
	int L = 0, R = INF, ans;
	while ( L <= R ) 
	{
		int Mid = L + R >> 1;
		if ( Check(Mid) ) { ans = Mid; R = Mid - 1; }
		else L = Mid + 1;
	}
	Check(ans);
	REP(i, 1, K) printf("%lld ", b[i]); puts("");
    return 0;
}
