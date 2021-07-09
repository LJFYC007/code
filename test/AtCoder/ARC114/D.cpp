/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2021年03月19日 星期五 10时27分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e4 + 10;
const int INF = 1e18;

int f[5010][maxn], n, m, k, a[maxn], b[maxn];
set<int> Set;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &k);
	REP(i, 1, n) 
	{ 
		scanf("%lld", &a[i]); 
		if ( Set.find(a[i]) != Set.end() ) Set.erase(a[i]);
		else Set.insert(a[i]);
	} 
	REP(i, 1, k) 
	{ 
		int x; scanf("%lld", &x); 
		if ( Set.find(x) != Set.end() ) Set.erase(x);
		else Set.insert(x);
	}
	sort(a + 1, a + n + 1);
	while ( !Set.empty() ) { b[++ m] = *Set.begin(); Set.erase(Set.begin()); } 
	REP(i, 0, n) REP(j, 0, m) f[i][j] = INF; f[0][0] = 0; f[1][1] = abs(a[1] - b[1]);
	REP(i, 2, n) for ( int j = (i & 1); j <= m; j += 2 ) 
	{
		f[i][j] = f[i - 2][j] + abs(a[i] - a[i - 1]);
		if ( j >= 1 ) f[i][j] = min(f[i][j], f[i - 1][j - 1] + abs(a[i] - b[j]));
	}
	if ( f[n][m] < INF ) printf("%lld\n", f[n][m]);
	else puts("-1");
    return 0;
}
