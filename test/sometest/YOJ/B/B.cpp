/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年02月21日 星期日 13时34分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;
const int INF = 1e9;

int n, m, b[maxn], a[maxn], c[maxn], r, d[maxn], ans;

inline bool Check(int x)
{
	REP(i, 1, m) d[i] = b[i];
	REP(i, 1, n) d[c[i]] -= a[i] * x;
	REP(i, 1, m) if ( d[i] < 0 ) return false;
	return true;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &m);
	REP(i, 1, m) { scanf("%lld", &b[i]); d[i] = b[i]; } 
	REP(i, 1, n) scanf("%lld%lld", &a[i], &c[i]);
	int num = 0, l = 1, r = INF;	
	while ( l <= r ) 
	{
		int Mid = (l + r) / 2;
		if ( Check(Mid) ) { num = Mid; l = Mid + 1; }
		else r = Mid - 1;
	}

	ans = num * n;	
	REP(i, 1, n) b[c[i]] -= a[i] * num;

	r = 0; int len = 0;
	REP(i, 1, n)
	{
		if ( len == 0 && r < i ) { r = i; len = 0; } 
		while ( b[c[r]] >= a[r] ) { b[c[r]] -= a[r]; ++ len; r = r == n ? 1 : r + 1; }
		printf("%lld ", ans + len);
		if ( len >= 1 ) { b[c[i]] += a[i]; -- len; } 
	}
	puts("");
    return 0;
}
