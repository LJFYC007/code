/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年07月16日 星期五 09时36分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int INF = 1e9 + 7;

inline int Query(int p, int sum, int k)
{
	int num = -1;
	REP(i, 0, 10000000) 
	{
		if ( i * (INF - p) > sum ) break ; 
		int x = (sum - i * (INF - p)) / p + 1;
		num += x; 
		if ( num >= k ) return true;
	}
	return false;
}

inline pii Find(int p, int k)
{
	int L = 0, R = INF * INF * 2, pos = 0;
	while ( L <= R ) 
	{
		int Mid = L + R >> 1; 
		if ( Query(p, Mid, k) ) { pos = Mid; R = Mid - 1; }
		else L = Mid + 1;
	}
	int A = 0, B = 0, cnt = -1;
	REP(i, 0, 10000000) 
	{
		if ( i * (INF - p) > pos || cnt == k ) break ; 
		int x = min(k - cnt, (pos - i * (INF - p)) / p + 1);
		cnt += x; A += x * i; B += x * (x - 1) / 2;
	}
	return pii(A, B);
}

inline bool Check(int k, int A, int B)
{
	int L = 1, R = INF - 1, pos = -1; pii x;
	while ( L <= R ) 
	{
		int Mid = L + R >> 1; pii t = Find(Mid, k);
		if ( t.first <= A ) { L = Mid + 1; x = t; pos = Mid; }
		else R = Mid - 1;
	}
	if ( pos != -1 && (INF - pos) * x.first + pos * x.second <= (INF - pos) * A + pos * B ) return true;
	return false;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	int A, B; scanf("%lld%lld", &A, &B);
	if ( A > B ) swap(A, B);
	int ans = 0, L = 1, R = 2000000;	
	while ( L <= R ) 
	{
		int Mid = L + R >> 1;
		if ( Check(Mid, A, B) ) { ans = Mid; L = Mid + 1; }
		else R = Mid - 1;
	}
	printf("%lld\n", ans);
    return 0;
}
