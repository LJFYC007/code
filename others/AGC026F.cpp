/***************************************************************
	File name: AGC026F.cpp
	Author: ljfcnyali
	Create time: 2021年04月26日 星期一 11时09分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3e5 + 10;
const int INF = 0x3f3f3f3f;

int n, a[maxn]; bool f[maxn];

inline bool Check(int val)
{
	int Min = 0, sum = 0; mem(f); f[0] = true;
	REP(i, 1, n)
	{
		sum += (i & 1 ? 1 : -1) * a[i];
		if ( i % 2 == 0 && f[i - 1] ) Min = min(Min, sum);
		if ( (i & 1) && sum - Min >= val ) f[i] = true;
	}
	return f[n];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); REP(i, 1, n) scanf("%d", &a[i]);
	int sum = 0, num = 0; REP(i, 1, n) { sum += a[i]; num += (i & 1 ? 0 : a[i]); }
	if ( n % 2 == 0 ) { printf("%d %d\n", max(num, sum - num), min(num, sum - num)); return 0; }
	int L = -INF, R = INF, ret = -INF;
	while ( L <= R ) 
	{
		int Mid = L + R >> 1;
		if ( Check(Mid) ) { L = Mid + 1; ret = Mid; } 
		else R = Mid - 1;
	}
	printf("%d %d\n", num + ret, sum - num - ret);
    return 0;
}
