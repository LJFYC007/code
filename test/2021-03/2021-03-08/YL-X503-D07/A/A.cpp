/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年03月08日 星期一 15时45分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1030;
const int Mod = 1e9 + 7;

int n, k, f[maxn][maxn], g[maxn][maxn], h[maxn][maxn], t[maxn][maxn];
int Min[maxn][20], Max[maxn][20], Log[maxn], s[maxn][maxn];
bool vis[maxn][maxn], use[maxn][maxn];
vector<int> p[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &k, &n);
	REP(j, 1, k) { p[j].resize(n + 1); REP(i, 1, n) scanf("%lld", &p[j][i]); }
	REP(i, 2, n) Log[i] = Log[i >> 1] + 1;
	memset(vis, true, sizeof(vis));
	REP(o, 1, k) 
	{
		REP(i, 1, n) Min[i][0] = Max[i][0] = p[o][i];
		REP(j, 1, 9) REP(i, 1, n) 
		{
			Min[i][j] = min(Min[i][j - 1], Min[i + (1 << j - 1)][j - 1]);
			Max[i][j] = max(Max[i][j - 1], Max[i + (1 << j - 1)][j - 1]);
		}
		mem(use);
		REP(i, 1, n) REP(j, i, n)
		{
			int x = Log[j - i + 1];
			int l = min(Min[i][x], Min[j - (1 << x) + 1][x]), r = max(Max[i][x], Max[j - (1 << x) + 1][x]);
			if ( r - l + 1 == j - i + 1 ) use[l][r] = true;
		}
		REP(i, 1, n) REP(j, i, n) if ( !use[i][j] ) vis[i][j] = false;
	}

	REP(i, 1, n) REP(j, i, n) s[i][j] = s[i][j - 1] + vis[i][j];

	REP(len, 1, n) REP(i, 1, n - len + 1)
	{
		int j = i + len - 1;
		REP(k, i, j - 1) 
		{ 
			f[i][j] = (f[i][j] + f[i][k] * (g[k + 1][j] + f[k + 1][j])) % Mod;
			g[i][j] = (g[i][j] + f[i][k] * (g[k + 1][j] + f[k + 1][j])) % Mod;
			h[i][j] = (h[i][j] + f[i][k] * f[k + 1][j]) % Mod;
			if ( vis[k + 1][j] && s[i][j - 1] - s[i][k] >= 1 ) 
				t[i][j] = (t[i][j] + f[i][k] * (t[k + 1][j] + h[k + 1][j])) % Mod;
		}
		f[i][j] = (f[i][j] + t[i][j]) % Mod;
		if ( !vis[i][j] ) f[i][j] = 0;
		if ( vis[i][j] && !f[i][j] ) f[i][j] = 1;
	}
	printf("%lld\n", (f[1][n] + Mod) % Mod);
    return 0;
}
