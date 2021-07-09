/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年05月08日 星期三 09时31分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;

int a[maxn], n, m, ans;

inline bool pd(int x)
{
	int last = a[1], sum = 1;
	REP(i, 2, n)
	{
		if ( a[i] - last >= x ) { ++ sum; last = a[i]; }
		if ( sum >= m ) return true;
	}
	return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, n) scanf("%d", &a[i]);
	sort ( a + 1, a + n + 1 );
	int L = 1, R = a[n];
	while ( L <= R ) 
	{
		int Mid = (L + R) / 2;
		if ( pd(Mid) )
		{
			ans = max(ans, Mid);
			L = Mid + 1;
		}
		else R = Mid - 1;
	}
	printf("%d\n", ans);
    return 0;
}
