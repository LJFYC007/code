#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 998244353;

int n, m, N, a[maxn], ans, f[maxn][2], h[maxn][2], g[10][maxn][2], p[maxn];
char s[maxn];

inline int get(int l, int r) { return ((l + r) * (r - l + 1) / 2) % Mod; }

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int Solve3(int x, bool op)
{
	if ( !x ) return 1;
	if ( h[x][op] ) return h[x][op];
	int Max = op ? s[x] - '0' : 9, ret = 0;
	REP(i, 0, Max) ret = (ret + Solve3(x - 1, op & (i == Max))) % Mod;
	h[x][op] = ret; return ret;
}

inline int Solve2(int x, int val, bool op)
{
	if ( !x ) return 0;
	if ( g[val][x][op] ) return g[val][x][op];
	int Max = op ? s[x] - '0' : 9, ret = 0;
	REP(i, 0, Max)
		ret = (ret + (i < val) * Solve3(x - 1, op & (i == Max)) + Solve2(x - 1, val, op & (i == Max))) % Mod;
	g[val][x][op] = ret;
	return ret;
}

inline int Solve1(int x, bool op)
{
	if ( !x ) return 0;
	if ( f[x][op] ) return f[x][op];
	int Max = op ? s[x] - '0' : 9, ret = 0;
	REP(i, 0, Max)
	{
		if ( i ) ret = (ret + Solve2(x - 1, i, op & (i == Max))) % Mod;
		ret = (ret + Solve1(x - 1, op & (i == Max))) % Mod;
	}
	f[x][op] = ret;
	return ret;
}

inline int Solve0(int x, bool op)
{
	if ( !x ) return 0;
	if ( f[x][op] ) return f[x][op];
	int Max = op ? s[x] - '0' : 9, ret = 0;
	REP(i, 0, Max)
	{
		if ( x == N && !i ) continue ;
		int sum = i * p[n - x] % Mod;
		sum = sum * Solve3(x - 1, op & (i == Max)) % Mod;
		ret = (ret + sum + Solve0(x - 1, op & (i == Max))) % Mod;
	}
	f[x][op] = ret;
	return ret;
}

signed main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);

	p[0] = 1; REP(i, 1, maxn - 10) p[i] = p[i - 1] * 10 % Mod;

	scanf("%s", s + 1); n = str(s + 1);
	REP(i, 1, maxn - 10)
	{
		int x = i, ret = 0, cnt = 0; m = 0;
		while ( x ) { a[++ m] = x % 10; x /= 10; if ( a[m] != 0 ) ++ cnt; }
		if ( !a[1] || m > n ) continue ;
		REP(j, 1, m - 1) REP(k, j + 1, m) if ( a[j] > a[k] ) ++ ret;
		int L = ret > i ? 0 : (i - ret) / cnt;
		if ( L * cnt + ret <= i ) ++ L;
		int R = n - m; bool flag = false;
		REP(j, 1, m)
			if ( a[j] > s[j] - '0' ) { flag = true; break ; }
			else if ( a[j] < s[j] - '0' ) break ;
		if ( flag == true ) -- R;
		if ( L <= R )
		{
			ans = (ans + (ret - i) * (R - L + 1)) % Mod;
			ans = (ans + cnt * get(L, R)) % Mod;
		}
	}
	ans = (ans * 2) % Mod;

	reverse(s + 1, s + n + 1);
	ans = (ans - Solve1(n, 1)) % Mod;
	mem(f);
	N = n; ans = (ans + Solve0(n, 1)) % Mod;
	int x = 45;
	REP(i, 1, n - 1)
	{
		ans = (ans + x) % Mod;
		x = x * 100 % Mod;
	}
	/*
	for ( int i = n; i >= 1; -- i )
	{
		N = i;
		ans = (ans + Solve0(i, i == n ? 1 : 0) * power(p[n - i], Mod - 2)) % Mod;
		cerr << i << " " << Solve0(i, i == n ? 1 : 0) * power(p[n - i], Mod - 2) % Mod << endl;
	}
	cerr << get(10, 95) << endl;
	*/

	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}
