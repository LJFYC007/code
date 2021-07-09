/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年02月23日 星期二 17时40分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int T, n, a[maxn], p[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d", &n); REP(i, 1, n) { scanf("%d", &a[i]); p[a[i]] = i; } 
		int lst = n;
		for ( int i = n; i >= 1; -- i ) 
		{
			if ( !p[i] ) continue ; 
			REP(j, p[i], lst) printf("%d ", a[j]); ;
			int x = p[i] - 1;
			REP(j, p[i], lst) p[a[j]] = 0;
			lst = x;
		}
		puts("");
	}
    return 0;
}
