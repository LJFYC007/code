/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年07月15日 星期四 09时03分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int val[7], A[7] = {0, 1, 3, 5, 2, 4, 6}, B[7] = {0, 2, 6, 3, 4, 1, 5};
struct node { int p[7], num[7]; } ;

node operator * (node a, node b)
{
	node c;
	REP(i, 1, 6) c.p[i] = b.p[a.p[i]];
	REP(i, 1, 6) c.num[i] = a.num[i] + b.num[a.p[i]];
	return c;
}

inline node power(node a, int b)
{
	node r = a; -- b;
	while ( b ) { if ( b & 1 ) r = r * a; a = a * a; b >>= 1; }
	return r;
}

inline node Solve(int a, int b, node R, node U)
{
	if ( a < b ) { swap(a, b); swap(R, U); }
	if ( b == 1 ) return power(R, a - 1);
	int num = a / b;
	return Solve(a % b, b, R, power(R, num) * U) * power(R, num);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	int a, b; scanf("%lld%lld", &a, &b);
	REP(i, 1, 6) scanf("%lld", &val[i]);
	node R, U; REP(i, 1, 6) R.num[i] = U.num[i] = 0;
	R.num[3] = 1; REP(i, 1, 6) R.p[i] = A[i]; 
	U.num[6] = 1; REP(i, 1, 6) U.p[i] = B[i];
	node ans = Solve(a, b, R, U);
	int ret = val[5];
	REP(i, 1, 6) ret += val[i] * ans.num[i];
	printf("%lld\n", ret);
    return 0;
}
