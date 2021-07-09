/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年04月08日 星期四 11时22分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
#define int long long
typedef long long LL;

const int maxn = 310;
const int Mod = 1e9 + 7;

int T, n, a[maxn][maxn], f[maxn][maxn], Max, ans;
int dt[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
vector<pii> p[maxn * maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &T);
	while ( T -- ) 
	{
		int L, R; scanf("%lld%lld", &L, &R); n = R - L + 1;
		REP(i, 0, n * n) p[i].clear();
		REP(i, 0, n - 1) REP(j, 0, n - 1) 
		{ 
			a[i][j] = (L + i) ^ (L + j); 
			if ( a[i][j] <= n * n ) p[a[i][j]].push_back(pii(i, j)); 
			f[i][j] = a[i][j] == 0 ? 1 : 0;
		}
		ans = Max = 0;
		REP(i, 0, n * n) for ( auto it : p[i] ) 
		{
			REP(j, 0, 3)
			{
				int u = it.x + dt[j][0], v = it.y + dt[j][1];
				if ( u >= 0 && v >= 0 && u < n && v < n && a[u][v] == i - 1 ) f[it.x][it.y] = (f[it.x][it.y] + f[u][v]) % Mod;
			}
			if ( f[it.x][it.y] )
			{
				if ( i > Max ) { Max = i; ans = 0; }
				ans = (ans + f[it.x][it.y]) % Mod;
			}
		}
		printf("%lld %lld\n", Max, ans);
	}
    return 0;
}
