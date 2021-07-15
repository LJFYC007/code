/***************************************************************
	File name: AGC028E.cpp
	Author: ljfcnyali
	Create time: 2021年07月14日 星期三 21时36分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e3 + 10;

int n, m, Max, a[maxn], p[maxn];
bool f[maxn][maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n)
	{
		scanf("%d", &a[i]);
		if ( a[i] > Max ) { Max = a[i]; ++ m; p[i] = 2; }
		else p[i] = 1;
	}
	f[n + 1][0] = true;
	for ( int i = n; i >= 1; -- i ) REP(k, a[i] + 1, n + 1) REP(j, 0, m) 
		f[a[i]][j + p[i]] |= f[k][j];

	int sum = 0, pos = 0;
	REP(i, 1, n) 
	{
		REP(j, 1, m) f[a[i]][j] = false;
		bool flag = false; REP(j, pos + 1, m) if ( f[j][m - sum] ) flag = true;
		if ( flag ) printf("0");
		else { printf("1"); if ( a[i] > pos ) { sum += p[i]; pos = a[i]; } }
	}
	puts("");

	sum = pos = 0;
	REP(i, 1, n) if ( a[i] > pos ) 
	{
		if ( sum <= m && f[a[i]][m - sum] ) { printf("0"); sum += p[i]; pos = a[i]; }
		else printf("1");
	}
	else printf("0");
    return 0;
}
