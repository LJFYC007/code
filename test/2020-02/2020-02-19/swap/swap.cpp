#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int seed1 = 37;
const int Mod1 = 1e9 + 7;
const int seed2 = 233;
const int Mod2 = 998244353;

int n, p1[maxn], inv1[maxn], p2[maxn], inv2[maxn], ans, f[3][maxn], tot[3], pre1[3][maxn], suf1[3][maxn], pre2[3][maxn], suf2[3][maxn];
char s[maxn];
map<int, int> Map1, Map2;

inline int power(int a, int b, int Mod) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void Insert(int x, int op)
{
	if ( tot[op] && f[op][tot[op]] == x )  -- tot[op];
	else
	{
		f[op][++ tot[op]] = x;
		pre1[op][tot[op]] = (pre1[op][tot[op] - 1] + x * p1[tot[op] - 1]) % Mod1;
		suf1[op][tot[op]] = (suf1[op][tot[op] - 1] * seed1 + x) % Mod1;
		pre2[op][tot[op]] = (pre2[op][tot[op] - 1] + x * p2[tot[op] - 1]) % Mod2;
		suf2[op][tot[op]] = (suf2[op][tot[op] - 1] * seed2 + x) % Mod2;
	}
}

inline int Find(int op, int L, int R, int d)
{
	if ( d == 0 )
	{
		int ret = (pre1[op][R] - pre1[op][L - 1]) * inv1[L - 1] % Mod1;
		return (ret + Mod1) % Mod1;
	}
	else
	{
		L = tot[op] - L + 1;
		R = tot[op] - R + 1;
		swap(L, R);
		int ret = (suf1[op][R] - suf1[op][L - 1] * p1[R - L + 1]) % Mod1;
		return (ret + Mod1) % Mod1;
	}
}

inline int Find1(int op, int L, int R, int d)
{
	if ( d == 0 )
	{
		int ret = (pre2[op][R] - pre2[op][L - 1]) * inv2[L - 1] % Mod2;
		return (ret + Mod2) % Mod2;
	}
	else
	{
		L = tot[op] - L + 1;
		R = tot[op] - R + 1;
		swap(L, R);
		int ret = (suf2[op][R] - suf2[op][L - 1] * p2[R - L + 1]) % Mod2;
		return (ret + Mod2) % Mod2;
	}
}

inline void Get(int l, int r, int x, int y, int op)
{
	if ( op == 1 )
	{
		tot[0] = 0; for ( int i = r; i >= l; -- i ) Insert(s[i] - 'a' + 1, 0);
		REP(i, l, r)
		{
			Insert(s[i] - 'a' + 1, 0);
			if ( s[i] == x + 'a' - 1 )
			{
				Insert(y, 1);
				int L = 1, R = min(tot[1], tot[0]), len = 0;
				while ( L <= R )
				{
					int Mid = L + R >> 1;
					if ( Find(1, tot[1] - Mid + 1, tot[1], 0) == Find(0, tot[0] - Mid + 1, tot[0], 0)
					  && Find1(1, tot[1] - Mid + 1, tot[1], 0) == Find1(0, tot[0] - Mid + 1, tot[0], 0)
					) { L = Mid + 1; len = Mid; }
					else R = Mid - 1;
				}
				int sum1 = (Find(1, 1, tot[1] - len, 0) + Find(0, len + 1, tot[0], 1) * p1[tot[1] - len]) % Mod1;
				sum1 = (sum1 + Mod1) % Mod1; ++ Map1[sum1];
				int sum2 = (Find1(1, 1, tot[1] - len, 0) + Find1(0, len + 1, tot[0], 1) * p2[tot[1] - len]) % Mod2;
				sum2 = (sum2 + Mod2) % Mod2; ++ Map2[sum2];
				Insert(y, 1);
			}
			Insert(s[i] - 'a' + 1, 1);
		}
		for ( int i = r; i >= l; -- i ) Insert(s[i] - 'a' + 1, 1);
	}
	else
	{
		tot[0] = 0; for ( int i = r; i >= l; -- i ) Insert(s[i] - 'a' + 1, 2);
		REP(i, l, r)
		{
			Insert(s[i] - 'a' + 1, 2);
			if ( s[i] == x + 'a' - 1 )
			{
				Insert(y, 0);
				int L = 1, R = min(tot[0], tot[2]), len = 0;
				while ( L <= R )
				{
					int Mid = L + R >> 1;
					if ( Find(0, tot[0] - Mid + 1, tot[0], 0) == Find(2, tot[2] - Mid + 1, tot[2], 0)
					&& Find1(0, tot[0] - Mid + 1, tot[0], 0) == Find1(2, tot[2] - Mid + 1, tot[2], 0)
					) { L = Mid + 1; len = Mid; }
					else R = Mid - 1;
				}
				int sum1 = (Find(2, 1, tot[2] - len, 0) + suf1[0][tot[0] - len] * p1[tot[2] - len]) % Mod1;
				sum1 = (sum1 + Mod1) % Mod1;
				int sum2 = (Find1(2, 1, tot[2] - len, 0) + suf2[0][tot[0] - len] * p2[tot[2] - len]) % Mod2;
				sum2 = (sum2 + Mod2) % Mod2;
				ans += min(Map1[sum1], Map2[sum2]);
				Insert(y, 0);
			}
			Insert(s[i] - 'a' + 1, 0);
		}
	}
}

inline void Solve(int l, int r)
{
	if ( l >= r ) return ;
	int Mid = l + r >> 1;
	REP(i, 1, 3) REP(j, 1, 3)
	{
		if ( i == j ) continue ;
		Map1.clear(); Map2.clear();
		Get(l, Mid, i, j, 1);
		Get(Mid + 1, r, j, i, 0);
	}
	for ( int i = r; i > Mid; -- i ) Insert(s[i] - 'a' + 1, 2);
	Solve(l, Mid);
	REP(i, Mid + 1, r) Insert(s[i] - 'a' + 1, 2);
	REP(i, l, Mid) Insert(s[i] - 'a' + 1, 1);
	Solve(Mid + 1, r);
	for ( int i = Mid; i >= l; -- i ) Insert(s[i] - 'a' + 1, 1);
}

signed main()
{
	freopen("swap.in", "r", stdin);
	freopen("swap.out", "w", stdout);
	scanf("%s", s + 1); n = str(s + 1);
	p1[0] = 1; REP(i, 1, n) p1[i] = p1[i - 1] * seed1 % Mod1;
	inv1[0] = 1; REP(i, 1, n) inv1[i] = inv1[i - 1] * power(seed1, Mod1 - 2, Mod1) % Mod1;
	p2[0] = 1; REP(i, 1, n) p2[i] = p2[i - 1] * seed2 % Mod2;
	inv2[0] = 1; REP(i, 1, n) inv2[i] = inv2[i - 1] * power(seed2, Mod2 - 2, Mod2) % Mod2;
	Solve(1, n);
	printf("%lld\n", ans);
	return 0;
}
