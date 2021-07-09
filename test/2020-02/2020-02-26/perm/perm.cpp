#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 4e6 + 10;
const int Mod = 950009857;

int r[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r ; }

inline void NTT(int *f, int n, int inv)
{
	REP(i, 1, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
	REP(i, 0, n - 1) if ( i < r[i] ) swap(f[i], f[r[i]]);
	for ( int Mid = 1; Mid < n; Mid <<= 1 )
	{
		int tmp = power(7, (Mod - 1) / (Mid << 1));
		if ( inv == -1 ) tmp = power(tmp, Mod - 2);
		for ( int i = 0; i < n; i += (Mid << 1) )
		{
			int sum = 1;
			for ( int j = 0; j < Mid; ++ j, sum = sum * tmp % Mod )
			{
				int x = f[i + j], y = sum * f[i + Mid + j] % Mod;
				f[i + j] = (x + y) % Mod; f[i + Mid + j] = (x - y) % Mod;
			}
		}
	}
	if ( inv == -1 )
	{
		inv = power(n, Mod - 2);
		REP(i, 0, n - 1) f[i] = f[i] * inv % Mod;
	}
}

int n, k, fac[maxn], inv[maxn], a[maxn], F[maxn], G[maxn];

inline void Solve(int l, int r)
{
	if ( l == r ) return ;
	int Mid = l + r >> 1; Solve(l, Mid);
	int a[maxn], b[maxn];
    int n = r - l, len = 1;
	while ( len < (n << 1) ) len <<= 1;
    REP(i, 0, len - 1) a[i] = b[i] = 0;
	REP(i, l, Mid) a[i - l] = F[i]; REP(i, 1, r - l) b[i - 1] = G[i];
	NTT(a, len, 1); NTT(b, len, 1); REP(i, 0, len - 1) a[i] = a[i] * b[i] % Mod; NTT(a, len, -1);
	int tot = Mid;
	REP(i, Mid - l, r - l - 1) { ++ tot; F[tot] = (F[tot] + a[i] * power(tot, Mod - 2)) % Mod; }
	Solve(Mid + 1, r);
}

signed main()
{
	freopen("perm.in", "r", stdin);
	freopen("perm.out", "w", stdout);
	scanf("%lld%lld", &n, &k);
	fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	F[0] = G[0] = 1;
	REP(i, 1, k) { scanf("%lld", &a[i]); G[a[i]] = 1; }
	Solve(0, n);
	REP(i, 1, n) F[i] = F[i] * fac[i] % Mod;
	REP(i, 1, n) printf("%lld\n", (F[i] + Mod) % Mod);
	return 0;
}
