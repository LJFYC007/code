/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2021年03月14日 星期日 08时38分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, q, a[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &q); REP(i, 1, n) scanf("%d", &a[i]);	
	while ( q -- ) 
	{
		int op, l, r, x; scanf("%d%d%d", &op, &l, &r);
		if ( op == 1 ) 
		{
			scanf("%d", &x);
			REP(i, l, r) a[i] &= x; 
		}
		if ( op == 2 ) 
		{
			scanf("%d", &x);
			REP(i, l, r) a[i] |= x; 
		}
		if ( op == 3 ) 
		{
			int ret = 0; REP(i, l, r) ret = max(ret, a[i]);
			printf("%d\n", ret);
		}
		// REP(i, 1, n) printf("%d ", a[i]); puts("");
	}
    return 0;
}
