/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年06月27日 星期日 20时22分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5010;
const int Mod = 998244353;

int n, k, f[maxn][maxn], a[maxn], g[maxn][maxn], ans;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &k);
	REP(i, 1, n) scanf("%d", &a[i]);
	REP(j, 1, n) REP(i, 1, n) g[i][j] = g[i - 1][j] + (a[i] > j);
	
	int ans = 1;
	REP(i, 1, n - 1) if ( a[i] < a[i + 1] && g[i][a[i]] == k ) 
		ans = 1ll * ans * (n - i + 1) % Mod;
	printf("%d\n", ans);
    return 0;
}
