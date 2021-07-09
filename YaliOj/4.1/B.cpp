/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年05月28日 星期二 15时11分52秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 50010;
const int Max = 32010;

int ans[maxn], c[maxn], n;

inline int lowbit(int x) { return x & (-x); }

inline void add(int x, int val)
{
	for ( int i = x; i <= Max; i += lowbit(i) ) c[i] += val;
}

inline int getsum(int x)
{
	int sum = 0;
	for ( int i = x; i >= 1; i -= lowbit(i) ) sum += c[i];
	return sum;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n)
	{
		int x, y; scanf("%d%d", &x, &y);
		++ x;
		ans[getsum(x)] ++;
//		printf("%d %d\n", i, getsum(x));
		add(x, 1);
//		REP(j, 1, n) printf("%d ", c[j]); puts("");
	}
	REP(i, 0, n - 1) printf("%d\n", ans[i]);
    return 0;
}
