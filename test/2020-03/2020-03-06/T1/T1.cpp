#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1030;
const int Mod = 1e9 + 7;

int n, m, b[11], ans, f[11][11][31][31];

inline int Solve1(int l, int r, int L, int R)
{
	if ( l > r || R <= 0 ) return 1; if ( L > R ) return 0;
	if ( f[l][r][L][R] != -1 ) return f[l][r][L][R];
	int ret = 0, x = L;
	if ( l == r )
	{
		if ( L == 0 ) { ++ ret; L = 1; }
		REP(i, L, R)
		{
			if ( !((b[l] >> i - 1) & 1) ) continue ;
			int x = 1;
			REP(j, 1, i - 1) if ( (b[l] >> j - 1) & 1 ) x = x * 2 % Mod;
			ret = (ret + x) % Mod;
		}
		f[l][r][x][R] = ret; return ret;
	}
	if ( L == 0 ) { ret = (ret + Solve1(l + 1, r, L, R)) % Mod; L = 1; }
	REP(j, L, R)
	{
		int i = l;
		if ( !((b[i] >> j - 1) & 1) ) continue ;
		ret = (ret + Solve1(l, i, 0, j - 1) * Solve1(i + 1, r, j + 1, R)) % Mod;
		while ( i < r && ((b[i + 1] >> j - 1) & 1) )
		{
			++ i;
			ret = (ret + Solve1(l, i, 0, j - 1) * Solve1(i + 1, r, j + 1, R)) % Mod;
		}
	}
	f[l][r][x][R] = ret; return ret;
}

inline bool Check(int x, int L, int R)
{
	REP(i, L, R) if ( (x >> i - 1) & 1 ) return false;
	return true;
}

inline int Solve2(int l, int r, int L, int R)
{
	if ( l > r || R <= 0 ) return 1; if ( L > R ) return 0;
	if ( f[l][r][L][R] != -1 ) return f[l][r][L][R];
	int ret = 0, x = L;
	if ( l == r )
	{
		if ( L == 0 ) { ret += Check(b[l], 1, R); L = 1; }
		for ( int i = R; i >= L; -- i )
			if ( (b[l] >> i - 1) & 1 )
			{
				int x = 1;
				REP(j, 1, i - 1) if ( !((b[l] >> j - 1) & 1) ) x = x * 2 % Mod;
				ret = (ret + x) % Mod;
				break ;
			}
		REP(i, L, R)
		{
			if ( !Check(b[l], i, R) ) continue ;
			int x = 1;
			REP(j, 1, i - 1) if ( !((b[l] >> j - 1) & 1) ) x = x * 2 % Mod;
			ret = (ret + x) % Mod;
		}
		f[l][r][x][R] = ret; return ret;
	}
	if ( L == 0 )
	{
		if ( Check(b[l], 1, R) ) ret = (ret + Solve2(l + 1, r, L, R)) % Mod;
		L = 1;
	}
	REP(j, L, R)
	{
		int i = l;
		if ( !Check(b[i], j + 1, R) ) continue ;
		int x = ret;
		ret = (ret + Solve2(l, i, 0, j - 1) * Solve2(i + 1, r, j + 1, R)) % Mod;
		while ( i < r && Check(b[i + 1], j + 1, R) )
		{
			++ i;
			ret = (ret + Solve2(l, i, 0, j - 1) * Solve2(i + 1, r, j + 1, R)) % Mod;
		}
	}
	f[l][r][x][R] = ret; return ret;
}

signed main()
{
	freopen("and.in", "r", stdin);
	freopen("and.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	REP(i, 1, n) scanf("%lld", &b[i]);
	memset(f, -1, sizeof(f));
	int ans1 = Solve1(1, n, 0, m);
	reverse(b + 1, b + n + 1);
	memset(f, -1, sizeof(f));
	int ans2 = Solve2(1, n, 0, m);
	printf("%lld\n", ans1 * ans2 % Mod);
	return 0;
}
