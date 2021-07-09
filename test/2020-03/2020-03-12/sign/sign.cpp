#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;
const int Mod = 998244353;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

int r[maxn];

inline void NTT(int *f, int n, int inv)
{
	REP(i, 1, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
	REP(i, 0, n - 1) if ( r[i] > i ) swap(f[i], f[r[i]]);
	for ( int Mid = 1; Mid < n; Mid <<= 1 )
	{
		int tmp = power(3, (Mod + 1) / (Mid << 1));
		if ( inv == -1 ) tmp = power(tmp, Mod - 2);
		for ( int i = 0; i < n; i += (Mid << 1) )
		{
			int sum = 1;
			for ( int j = 0; j < Mid; ++ j, sum = sum * tmp % Mod )
			{
				int x = f[i + j], y = f[i + Mid + j] * sum % Mod;
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

int n, f[maxn], g[maxn], ret;
char s[maxn];
bool ans[maxn];

signed main()
{
	freopen("sign.in", "r", stdin);
	freopen("sign.out", "w", stdout);
	scanf("%lld", &n);
	scanf("%s", s + 1);

	int m = 1; while ( m < (n << 1) ) m <<= 1;

	memset(ans, true, sizeof(ans));
	mem(f); mem(g);
	REP(i, 1, n) if ( s[i] == 'a' ) f[i] = 1; else if ( s[i] == 'd' ) g[n - i + 1] = 1;
	NTT(f, m, 1); NTT(g, m, 1);
	REP(i, 0, m - 1) f[i] = f[i] * g[i] % Mod;
	NTT(f, m, -1);
	REP(i, 2, n) if ( f[i] != 0 ) ans[n - i + 1] = false;
	REP(i, 1, n - 1) for ( int j = i + i; j < n; j += i ) if ( !ans[j] ) ans[i] = false;

	mem(f); mem(g);
	REP(i, 1, n) if ( s[i] == 'd' ) f[i] = 1; else if ( s[i] == 'a' ) g[n - i + 1] = 1;
	NTT(f, m, 1); NTT(g, m, 1);
	REP(i, 0, m - 1) f[i] = f[i] * g[i] % Mod;
	NTT(f, m, -1);
	REP(i, 2, n) if ( f[i] != 0 ) ans[n - i + 1] = false;
	REP(i, 1, n - 1) for ( int j = i + i; j < n; j += i ) if ( !ans[j] ) ans[i] = false;

	REP(i, 1, n - 1) if ( ans[i] ) ret ^= i;
	printf("%lld\n", ret);
	return 0;
}
