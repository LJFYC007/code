/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), -1, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 60;

int n, m, Mod, p[maxn * maxn], C[maxn][maxn];
int f[maxn][10], g[maxn][maxn][10], h[maxn][maxn][10][1 << 10];

inline int H(int s, int t, int m, int x)
{
	if ( s > t ) swap(s, t);
	if ( x >= (1 << m) ) return 0;
	if ( !s || !t ) return p[(s + t) * m];
	if ( x <= 0 ) return p[(s + t) * m];
	if ( h[s][t][m][x] != -1 ) return h[s][t][m][x];
	int ret = 0;
	REP(i, 0, s) REP(j, 0, t)
		if ( (!i && j == t) || (!j && i == s) ) ret = (ret + H(s, t, m - 1, x - (1 << m - 1))) % Mod;
		else ret = (ret + (C[s][i] * C[t][j] % Mod) * (H(i, j, m - 1, x) * H(s - i, t - j, m - 1, x) % Mod)) % Mod;
	h[s][t][m][x] = ret; return ret;
}

inline int G(int s, int t, int m)
{
	if ( s > t ) swap(s, t);
	if ( !m ) return 0;
	if ( g[s][t][m] != -1 ) return g[s][t][m];
	int ret = 0;
	REP(i, 1, (1 << m) - 1) ret = (ret + H(s, t, m, i)) % Mod;
	g[s][t][m] = ret; return ret;
}

inline int F(int n, int m)
{
	if ( n == 1 || m == 0 ) return 0;
	if ( f[n][m] != -1 ) return f[n][m];
	int ret = 2 * F(n, m - 1);
	REP(i, 1, n - 1)
	{
		int x = (p[(n - i) * (m - 1)] * F(i, m - 1) + p[i * (m - 1)] * F(n - i, m - 1)) % Mod;
		x = (x + G(i, n - i, m - 1)) % Mod;
		x = (x + p[(n + 1) * (m - 1)]) % Mod;
		ret = (ret + x * C[n][i]) % Mod;
	}
	f[n][m] = ret; return ret;
}

signed main()
{
	freopen("xor.in", "r", stdin);
	freopen("xor.out", "w", stdout);
	scanf("%lld%lld%lld", &n, &m, &Mod);
	p[0] = 1; REP(i, 1, maxn * maxn - 1) p[i] = p[i - 1] * 2 % Mod;
	REP(i, 0, n) C[i][0] = 1;
	REP(i, 1, n) REP(j, 1, i) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % Mod;
	mem(f); mem(g); mem(h);
	printf("%lld\n", (F(n, m) + Mod) % Mod);
    return 0;
}
