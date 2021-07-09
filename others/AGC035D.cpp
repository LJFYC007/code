/***************************************************************
	File name: AGC035D.cpp
	Author: ljfcnyali
	Create time: 2021年02月07日 星期日 20时33分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 20;
const int INF = 1e18;

int n, a[maxn], ans;
map<int, map<int, int> > f[maxn][maxn];

inline int Solve(int x, int y, int l, int r)
{
	if ( l > r ) return 0;
	if ( f[l][r][x].count(y) ) return f[l][r][x][y];
	int ret = INF;
	REP(k, l, r) ret = min(ret, Solve(x, x + y, l, k - 1) + Solve(x + y, y, k + 1, r) + (x + y) * a[k]);
	f[l][r][x][y] = ret; return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n) scanf("%lld", &a[i]);
	ans = a[1] + a[n] + Solve(1, 1, 2, n - 1);
	printf("%lld\n", ans);
    return 0;
}

