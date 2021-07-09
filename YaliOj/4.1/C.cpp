/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年05月28日 星期二 15时21分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 50010;

int c[maxn][2], n, m;

inline int lowbit(int x) { return x & (-x); }

inline void add(int x, int y, int p)
{
	for ( int i = x; i <= n; i += lowbit(i) ) c[i][p] += y;
}

inline int getsum(int x, int p)
{
	int sum = 0;
	for ( int i = x; i >= 1; i -= lowbit(i) ) sum += c[i][p];
	return sum;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, m)
	{
		int k, l, r; scanf("%d%d%d", &k, &l, &r);
		if ( k == 1 ) { add(l, 1, 0); add(r, 1, 1); }
		else printf("%d\n", getsum(r, 0) - getsum(l - 1, 1));
	}
    return 0;
}
