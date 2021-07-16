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

const int maxn = 1010;
const int m = 50;

map<int, int> f[maxn][41][41];

inline int Get(int A, int y)
{
	int sum = 0;
	while ( A >= y ) { ++ sum; A -= y; ++ y; } 
	return sum;
}

inline int Query(int A, int x, int y)
{
	int ret = 0;
	if ( x <= y + y + 1 && A >= x ) 
	{
		int num = (x + 1) / 2;
		while ( num && A >= x ) { ret += 2; A -= x; num --; }
		return ret + Query(A, x + 1, y);
	}
	else if ( A >= y + y + 1 + x * ((x + 1) / 2) ) 
		return 2 + Query(A - y - y - 1, x, y + 2);

	int sum = 0, num = (x + 1) / 2;;
	while ( A >= 0 && num >= 0 ) 
	{
		ret = max(ret, sum + Get(A, y));
		sum += 2; A -= x; -- num;
	}
	return ret;
}


inline int DFS(int A, int B, int k, int lst)
{
	if ( k > 40 ) return 0;
	// cerr << A << " " << k << " " << lst << endl;
	if ( f[A][k][lst].count(B) ) return f[A][k][lst][B];
	int sum = 0, num = 1, ret = 0;
	while ( B >= sum && num <= lst ) 
	{
		if ( num * k > A ) break ; 
		ret = max(ret, DFS(A - num * k, B - sum, k + 1, num) + num);
		sum += num; ++ num; 
	}
	f[A][k][lst][B] = ret; return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	int A, B; scanf("%lld%lld", &A, &B);
	if ( A <= 1000 && B <= 1000 ) 
	{
		// memset(f, -1, sizeof(f));
		printf("%lld\n", DFS(A, B, 0, 40) - 1);
	}
	else printf("%lld\n", Query(A, 1, 1));
    return 0;
}
