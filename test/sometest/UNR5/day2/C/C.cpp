/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年07月19日 星期一 11时25分36秒
***************************************************************/
#include<bits/stdc++.h>
#include "airline.h"

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2010;
const LL INF = 1e18;
const int maxm = 3e4 + 10;

map<int, int> Map;
LL f[maxn][maxn], dis[maxn][maxn], pre[maxm], suf[maxm];
int m, a[maxn];

LL solve(int n, int x, int y, int q, vector<int> P, int L)
{
	if ( q == 30000 ) 
	{
		LL ans = 0, l = 0, r = q - 1;
		while ( l <= r ) 
		{
			LL val1 = distance(x, P[r]);
			LL val2 = distance(y, P[l]);
			ans += max(val1, val2);
			if ( val1 > val2 ) { x = P[r]; -- r; }
			else { y = P[l]; ++ l; } 
			swap(x, y);
		}
		return ans;

	}
	Map[x] = ++ m; a[1] = x; 
	vector<int> p; p.push_back(y); for ( auto it : P ) p.push_back(it);
	for ( auto it : p ) if ( !Map.count(it) ) { Map[it] = ++ m; a[m] = it; } 
	REP(i, 0, q - 1) REP(j, 1, m) f[i][j] = -INF;
	REP(i, 1, m) REP(j, i + 1, m) dis[i][j] = dis[j][i] = distance(a[i], a[j]);
	REP(i, 0, q) p[i] = Map[p[i]];
	for ( int i = q - 1; i >= 0; -- i ) REP(j, 1, m)
	{
		f[i][j] = max(f[i][j], f[i + 1][j] + dis[p[i]][p[i + 1]]);
		f[i][j] = max(f[i][j], f[i + 1][p[i]] + dis[j][p[i + 1]]);
	}
	return f[0][1];	
}
