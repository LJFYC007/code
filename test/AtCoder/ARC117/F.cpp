/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2021年04月20日 星期二 15时24分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int INF = 1e12;

int n, m, a[maxn], L[maxn], R[maxn];

inline pii Solve(int x, int y)
{
	REP(i, 2, n)
	{
		if ( L[i] <= y - x && y - x <= R[i] ) continue ; 
		if ( y - x <= L[i] ) y = x + L[i];
		else x = y - R[i];
	}
	return pii(x, y);
}

inline bool Check(int x)
{
	REP(i, 1, n) 
	{
		L[i] = a[i]; R[i] = x - a[n + i]; 
		if ( L[i] > R[i] ) return false;
	}
	int l = L[1], r = R[1], pos = -1;
	while ( l <= r ) 
	{
		int Mid = l + r >> 1; pii t = Solve(0, Mid); 
		if ( t.first <= Mid ) { pos = Mid; r = Mid - 1; }
		else l = Mid + 1;
	}
	if ( pos != -1 && Solve(0, pos).second <= x ) return true;
	return false;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); REP(i, 1, n + n) scanf("%lld", &a[i]);
	int L = 0, R = INF, ans = 0;
	REP(i, 1, n + n) L = max(L, a[i]);
	while ( L <= R ) 
	{
		int Mid = L + R >> 1;
		if ( Check(Mid) ) { ans = Mid; R = Mid - 1; }
		else L = Mid + 1;
	}
	printf("%lld\n", ans);
    return 0;
}
