/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2021年02月23日 星期二 16时59分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int a, b, k, n, num;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &a, &b, &k);
	-- b; ++ num;
	if ( !b || !a ) 
	{
		if ( k >= 1 ) puts("No");
		else { 
			puts("Yes");
		REP(i, 1, num + b) printf("1"); REP(i, 1, a) printf("0"); puts(""); 
		REP(i, 1, num + b) printf("1"); REP(i, 1, a) printf("0"); puts(""); 
		}
		return 0; 
	}
	n = a + b - 1;
	if ( k > n ) { puts("No"); return 0; } 
	puts("Yes");
	if ( k == 0 ) 
	{
		REP(i, 1, num + b) printf("1"); REP(i, 1, a) printf("0"); puts(""); 
		REP(i, 1, num + b) printf("1"); REP(i, 1, a) printf("0"); puts(""); 
		return 0;
	}
	while ( k < b ) { -- b; ++ num; } 
	REP(i, 1, num) printf("1"); REP(i, 1, b) printf("1"); REP(i, 1, a) printf("0"); puts("");
	REP(i, 1, num) printf("1"); printf("0"); REP(i, 1, b - 1) printf("1"); 	
	k -= b - 1; REP(i, 1, k - 1) printf("0"); printf("1"); REP(i, k, a - 1) printf("0"); puts("");
    return 0;
}
