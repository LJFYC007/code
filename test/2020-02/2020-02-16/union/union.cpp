#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1010;
const int maxm = 1 << 15;
const int Mod = 1e9 + 7;

int n, a[maxn][maxn], f[maxm], g[maxn], fa[maxn], ans;
bool vis[maxn][maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

inline bool Check()
{
	REP(i, 1, n) fa[i] = i;
	REP(i, 1, n) REP(j, i + 1, n) if ( vis[i][j] )
	{
		int fx = find(i), fy = find(j);
		if ( fx != fy ) fa[fx] = fy;
	}
	REP(i, 2, n) if ( find(1) != find(i) ) return false;
	return true;
}

inline void DFS(int x, int y, int sum)
{
	if ( x == n ) { if ( Check() ) ans = (ans + sum) % Mod; return ; }
	if ( y == n + 1 ) { DFS(x + 1, x + 2, sum); return ;  }
	vis[x][y] = true;
	DFS(x, y + 1, sum * a[x][y] % Mod);
	vis[x][y] = false;
	DFS(x, y + 1, sum);
}

signed main()
{
	freopen("union.in", "r", stdin);
	freopen("union.out", "w", stdout);
	scanf("%lld", &n);
	REP(i, 1, n) REP(j, i + 1, n) scanf("%lld", &a[i][j]);
	DFS(1, 2, 1);
	/*
	REP(i, 1, n) f[1 << i - 1] = 1;
	REP(i, 1, n) REP(j, i + 1, n)
	{
		REP(k, 0, (1 << n) - 1) g[k] = f[k];
		REP(s1, 0, (1 << n) - 1)
		{
			int x = s1;
			if ( (s1 >> i - 1) & 1 || (s1 >> j - 1) & 1 )
			{
				x |= 1 << j - 1;
				x |= 1 << i - 1;
				g[x] = (g[x] + f[s1] * a[i][j]) % Mod;
			}
		}
		REP(k, 0, (1 << n) - 1) f[k] = g[k];
	}
	REP(i, 0, (1 << n) - 1) printf("%lld ", f[i]); puts("");
	int ans = f[(1 << n) - 1] * power(2, Mod - 2) % Mod;*/
	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}
