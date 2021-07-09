/***************************************************************
	File name: interval.cpp
	Author: ljfcnyali
	Create time: 2021年06月30日 星期三 09时58分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 998244353;

int n, m, q, a[maxn], b[maxn];

inline int Solve(int l, int r, int n)
{
	int ret = 0;
	REP(i, 1, n) if ( b[i] != b[i + 1] ) ret = (ret + m - 1 - (i < n)) % Mod;
	REP(i, 1, n) REP(j, i + 1, n)
		if ( b[j] != b[j + 1] ) ret = (ret + m - 1) % Mod;
	REP(i, 1, n - 1) if ( b[i] != b[i + 1] )
		REP(j, i + 1, n) ret = (ret + m - (j < n)) % Mod;

	REP(i, 1, n - 1) REP(j, i + 1, n) if ( b[i] != b[i + 1] )
	{
		bool flag = true;
		REP(k, i + 2, j) if ( b[k] != b[k - 2] ) flag = false;
		if ( !flag ) continue ; 
		-- ret;
	}
	return ret;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("interval.in", "r", stdin);
    freopen("interval1.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &q);
	REP(i, 1, n) scanf("%d", &a[i]);

	while ( q -- ) 
	{
		int l, r; scanf("%d%d", &l, &r); 
		REP(i, l, r) b[i - l + 1] = a[i]; b[r - l + 2] = 0;
		printf("%d\n", Solve(l, r, r - l + 1));
	}
    return 0;
}
