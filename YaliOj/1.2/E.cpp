/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年05月08日 星期三 11时43分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 110;

int f[maxn][maxn], n, a[maxn], b[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	int ans = 0;
	scanf("%d", &n);
	REP(i, 1, n) scanf("%d%d", &a[i], &b[i]);
	REP(i, 1, n)
		REP(j, 1, i - 1)
			f[i][j] = f[j][i] = abs(a[i] - a[j]) + abs(b[i] - b[j]);
	REP(k, 1, n)
		REP(i, 1, n)
			REP(j, 1, n)
				f[i][j] = min(f[i][j], max(f[i][k], f[k][j]));
	REP(i, 1, n)
		REP(j, 1, i - 1) 
			ans = max(ans, f[i][j]);
	printf("%d\n", (ans + 1) / 2);
    return 0;
}
