#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 4010;
const int Mod = 998244353;

int n, A[maxn], B[maxn], ans[maxn], sum, fac[maxn], S1[maxn][maxn];
int Next[maxn], sum1, sum2, sum3, inv[maxn], deg[maxn], vis[maxn], dp[maxn];
int f[maxn], g[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

inline int AA(int n, int m) { return n < m ? 0 : fac[n] * inv[n - m] % Mod; }

inline void DFS(int u, int t)
{
	vis[u] = 1;
	if ( !Next[u] )
	{
		if ( u <= n && t > n ) ++ sum1;
		if ( u > n && t <= n ) ++ sum2;
		if ( u > n && t > n ) ++ sum3;
		return ;
	}
	if ( vis[Next[u]] ) { ++ sum; return ; }
	DFS(Next[u], t);
}

signed main()
{
	freopen("gift.in", "r", stdin);
	freopen("gift.out", "w", stdout);
	scanf("%lld", &n);
	REP(i, 1, n) scanf("%lld", &A[i]);
	REP(i, 1, n) scanf("%lld", &B[i]);
	fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	S1[0][0] = 1;
	REP(i, 1, n) REP(j, 1, i) S1[i][j] = ((i - 1) * S1[i - 1][j] + S1[i - 1][j - 1]) % Mod;

	memset(vis, 1, sizeof(vis));
	REP(i, 1, n)
	{
		int x = A[i] ? A[i] : i + n, y = B[i] ? B[i] : i + n;
		vis[x] = vis[y] = 0;
		if ( A[i] || B[i] ) { Next[x] = y; ++ deg[y]; }
	}
	for ( int i = n * 2; i >= 1; -- i ) if ( !deg[i] && !vis[i] ) DFS(i, i);
	for ( int i = n * 2; i >= 1; -- i ) if ( !vis[i] ) DFS(i, i);
	REP(i, 0, sum1) REP(j, i, sum1) f[i] = (f[i] + (C(sum1, j) * S1[j][i] % Mod) * AA(sum3 + sum1 - j, sum1 - j)) % Mod;
	REP(i, 0, sum1)
	{
		int tmp = 0, op = 1;
		REP(j, i, sum1) { tmp = (tmp + op * f[j] * C(j, i)) % Mod; op *= -1; }
		f[i] = tmp;
	}
	REP(i, 0, sum2) REP(j, i, sum2) g[i] = (g[i] + (C(sum2, j) * S1[j][i] % Mod) * AA(sum3 + sum2 - j, sum2 - j)) % Mod;
	REP(i, 0, sum2)
	{
		int tmp = 0, op = 1;
		REP(j, i, sum2) { tmp = (tmp + op * g[j] * C(j, i)) % Mod; op *= -1; }
		g[i] = tmp;
	}
	REP(i, 0, n) REP(j, 0, i) dp[i] = (dp[i] + f[j] * g[i - j]) % Mod;
	REP(i, 0, n) REP(j, 0, i) ans[i] = (ans[i] + dp[j] * S1[sum3][i - j]) % Mod;
	for ( int i = n; i >= 1; -- i ) printf("%d ", i >= sum ? ((ans[i - sum] * fac[sum3] % Mod) + Mod) % Mod: 0); puts("");
	return 0;
}
