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
typedef long long LL;

const int maxn = 52;
const int Mod = 1e9 + 9;

int n, m, k, C[maxn][maxn], g[maxn][maxn], N;

struct Matrix
{
	int f[maxn * maxn][maxn * maxn];
} F;

Matrix operator * (Matrix a, Matrix b)
{
	Matrix c; REP(i, 0, N) REP(j, 0, N) c.f[i][j] = 0;
	REP(i, 0, N) REP(k, 0, N) if ( a.f[i][k] ) 
	{
		const int t = a.f[i][k];
		REP(j, 0, N) c.f[i][j] = (c.f[i][j] + 1ll * t * b.f[k][j]) % Mod;
	}
	return c;
}

inline Matrix power(Matrix a, int b)
{
	Matrix r = a; b --; 
	while ( b ) { if ( b & 1 ) r = r * a; a = a * a; b >>= 1; }
	return r;
}

inline int id(int x, int y) { return g[x][y]; }

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &k);
	if ( n > 20 )
	{

		N = -1; REP(i, 0, n) REP(j, 0, n - i) g[i][j] = ++ N;
		REP(i, 0, n)
		{
			C[i][0] = 1;
			REP(j, 1, i) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % Mod;
		}
		while ( m -- )
		{
			int i, j; scanf("%d%d", &i, &j);
			REP(x, 0, n) REP(y, 0, n - x)
			{
				int z = n - x - y;
				REP(a, 0, x) REP(c, 0, 0) REP(b, 0, y) REP(d, 0, 0)
				{
					if ( a + b > i || c + d > j ) continue ; 
					int ret = 1ll * C[x][a + c] * C[y][b + d] % Mod;	
					ret = 1ll * ret * C[z][i + j - a - b - c - d] % Mod;
					ret = 1ll * ret * C[a + c][a] % Mod;
					ret = 1ll * ret * C[b + d][b] % Mod;
					ret = 1ll * ret * C[i + j - a - b - c - d][i - a - b] % Mod;

					int u = (x - a - c) + d + (i - a - b);
					int v = a + (y - b - d) + (j - c - d);

					F.f[id(x, y)][id(u, v)] = (F.f[id(x, y)][id(u, v)] + ret) % Mod;
				}
			}
		}

		F = power(F, k);
		REP(x, 0, n) { REP(y, 0, n - x) printf("%d ", F.f[id(0, 0)][id(x, y)]); puts(""); }


		return 0;
	}

	N = -1; REP(i, 0, n) REP(j, 0, n - i) g[i][j] = ++ N;
	REP(i, 0, n)
	{
		C[i][0] = 1;
		REP(j, 1, i) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % Mod;
	}
	while ( m -- )
	{
		int i, j; scanf("%d%d", &i, &j);
		REP(x, 0, n) REP(y, 0, n - x)
		{
			int z = n - x - y;
			REP(a, 0, x) REP(c, 0, x - a) REP(b, 0, y) REP(d, 0, y - b)
			{
				if ( a + b > i || c + d > j ) continue ; 
				int ret = 1ll * C[x][a + c] * C[y][b + d] % Mod;	
				ret = 1ll * ret * C[z][i + j - a - b - c - d] % Mod;
				ret = 1ll * ret * C[a + c][a] % Mod;
				ret = 1ll * ret * C[b + d][b] % Mod;
				ret = 1ll * ret * C[i + j - a - b - c - d][i - a - b] % Mod;

				int u = (x - a - c) + d + (i - a - b);
				int v = a + (y - b - d) + (j - c - d);

				F.f[id(x, y)][id(u, v)] = (F.f[id(x, y)][id(u, v)] + ret) % Mod;
			}
		}
	}

	F = power(F, k);
	REP(x, 0, n) { REP(y, 0, n - x) printf("%d ", F.f[id(0, 0)][id(x, y)]); puts(""); }
    return 0;
}
