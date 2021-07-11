/***************************************************************
	File name: AGC021D.cpp
	Author: ljfcnyali
	Create time: 2021年07月11日 星期日 11时47分35秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 310;

int n, k, f[maxn][maxn][maxn];
char s[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%s", s + 1); n = str(s + 1);
	scanf("%d", &k);
	REP(i, 1, n) for ( int j = n; j >= 1; -- j ) REP(o, 0, k)
	{
		f[i][j][o] = max(f[i][j][o], f[i][j + 1][o]);
		f[i][j][o] = max(f[i][j][o], f[i - 1][j][o]);
		if ( s[i] == s[j] ) f[i][j][o] = max(f[i][j][o], f[i - 1][j + 1][o] + 1);
		else f[i][j][o + 1] = max(f[i][j][o + 1], f[i - 1][j + 1][o] + 1);
	}
	int ans = 0;
	REP(i, 1, n) REP(o, 0, k) ans = max(ans, f[i][i][o] * 2 - 1);
	REP(i, 1, n - 1) REP(o, 0, k) ans = max(ans, f[i][i + 1][o] * 2);
	printf("%d\n", ans);
    return 0;
}
