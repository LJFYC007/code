/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年05月28日 星期二 15时41分03秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 5000010;

int c[maxn], n, m;

inline int lowbit(int x) { return x & (-x); }

inline void add(int x, int y) 
{
	for ( int i = x; i <= n; i += lowbit(i) ) c[i] += y;
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
		int x, p; getchar(); getchar(); char c = getchar();
		if ( c == 'A' ) { scanf("%d", &x); printf("%d\n", getsum(x)); continue; }
		scanf("%d%d", &x, &p);
		if ( c == 'C' ) p = -p;
		add(x, p);
	}
    return 0;
}
