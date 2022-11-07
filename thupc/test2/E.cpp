/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 110;
const int maxm = 110 * 110 * 4;
const int INF = 1e18;

int n, m, s, a[maxm], deg[maxm], Begin[maxm], Next[maxm], To[maxm], e, W[maxm];
int f[maxn][maxn][maxn][2];
queue<int> Q;
vector<int> A;

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ deg[v]; W[e] = w; }

inline void chkmax(int &x, int y) { x = max(x, y); }

inline pii Max(pii a, pii b) { return a.first * b.second > a.second * b.first ? a : b; }

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld", &n, &m, &s);
	REP(i, 1, n - 1) scanf("%lld", &a[i]);
	REP(i, 1, m) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); }
	REP(i, 1, n) if ( deg[i] == 0 ) Q.push(i);
	while ( !Q.empty() )
	{
		int u = Q.front(); Q.pop(); A.push_back(u);
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{
			int v = To[i]; -- deg[v];
			if ( !deg[v] ) Q.push(v);
		}
	}
	REP(i, 1, n) REP(j, 0, n) REP(k, 0, n) REP(o, 0, 1) f[i][j][k][o] = -INF;
	f[s][1][0][1] = 0;
	for ( int ccc = 0; ccc < A.size(); ++ ccc )
	{
		int u = A[ccc];
		REP(i, 1, n) REP(j, 0, i) REP(o, 0, 1) if ( f[u][i][j][o] >= 0 )
			for ( int iii = Begin[u]; iii; iii = Next[iii] )
			{
				int v = To[iii], w = W[iii];
				chkmax(f[v][i][(j + w) % (i + 1)][0], f[u][i][j][o] + a[i]);
				if ( (j + w) % (i + 1) == 0 )
					chkmax(f[v][i + 1][0][1], f[u][i][j][o] + a[i]);
			}
	}
	pii ans = pii(0, 1);
	REP(i, 1, n) REP(j, 2, n) if ( f[i][j][0][1] >= 0 ) 
		ans = Max(ans, pii(f[i][j][0][1], j - 1));
	int d = __gcd(ans.first, ans.second);
	printf("%lld %lld\n", ans.first / d, ans.second / d);
    return 0;
}
