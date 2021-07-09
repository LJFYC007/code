#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;
const int seed = 233;
const int Mod = 998244353;

int f[maxn][21], n, m, k, T, p[maxn], inv[maxn], Hash1[maxn], Hash2[maxn];
char s[maxn], t[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int Get1(int l, int r) { return (Hash1[r] - Hash1[l - 1] + Mod) * inv[l - 1] % Mod; }

inline int Get2(int l, int r) { return (Hash2[r] - Hash2[l - 1] + Mod) * inv[l - 1] % Mod; }

inline int get(int x, int y)
{
	int l = 0, r = min(n - x + 1, m - y + 1), len = 0;
	while ( l <= r )
	{
		int Mid = l + r >> 1;
		if ( Get1(x, x + Mid - 1) != Get2(y, y + Mid - 1) ) r = Mid - 1;
		else { l = Mid + 1; len = Mid; }
	}
	return len;
}

signed main()
{
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
	scanf("%lld", &T);
	while ( T -- )
	{
		scanf("%lld", &k);
		scanf("%s", s + 1); n = str(s + 1);
		scanf("%s", t + 1); m = str(t + 1);

		memset(f, -1, sizeof(f)); f[0][0] = 0;
		p[0] = inv[0] = 1; REP(i, 1, n) { p[i] = p[i - 1] * seed % Mod; inv[i] = inv[i - 1] * power(seed, Mod - 2) % Mod; }
		REP(i, 1, n) Hash1[i] = (Hash1[i - 1] + p[i] * (s[i] - 'a' + 1)) % Mod;
		REP(i, 1, m) Hash2[i] = (Hash2[i - 1] + p[i] * (t[i] - 'a' + 1)) % Mod;

		REP(i, 0, n - 1) REP(j, 0, k)
		{
			if ( f[i][j] == -1 ) continue ;
			f[i + 1][j] = max(f[i + 1][j], f[i][j]);
			int len = get(i + 1, f[i][j] + 1);
			f[i + len][j + 1] = max(f[i + len][j + 1], f[i][j] + len);
		}
		REP(i, 0, k) if ( f[n][i] == m ) { puts("Yes"); goto Finish ; }
		puts("No");
		Finish : ;
	}
	return 0;
}
