/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年05月29日 星期三 08时15分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 500010;

int c[maxn], n, m;

inline int lowbit(int x) { return x & (-x); }

inline void add(int x, int val)
{
	for ( int i = x; i <= n; i += lowbit(i) ) c[i] += val;
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
	scanf("%d%d", &n, &m);
	REP(i, 1, m)
	{
		int t, l, r; scanf("%d%d", &t, &l);
		if ( t == 1 ) { scanf("%d", &r); add(l, 1); add(r + 1, -1); }
		else printf("%d\n", getsum(l) % 2);
	}
    return 0;
}
