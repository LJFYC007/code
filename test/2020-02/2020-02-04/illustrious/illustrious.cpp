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
const int N = 1e6;

int T, f[maxn], sumg[maxn], a[maxn], h[maxn], g[maxn];

inline int Get(int L, int R) { return (L + R) * (R - L + 1) / 2; }

inline int G(int n)
{
	int pos = upper_bound(a + 1, a + N + 1, n) - a - 1, ret = sumg[pos - 1];
	ret = ret + pos * Get(a[pos], n);
	return ret % Mod;
}

inline int Solve(int n)
{
	int pos = upper_bound(a + 1, a + N + 1, n) - a - 1;
	return (h[pos - 1] + G(n)) % Mod;
}

signed main()
{
	freopen("i.in", "r", stdin);
	freopen("i.out", "w", stdout);
	scanf("%lld", &T);
	f[1] = 1; REP(i, 2, N) f[i] = f[i - f[f[i - 1]]] + 1;
	REP(i, 1, N) g[i] = g[i - 1] + f[i];
	int x = 1;
	REP(i, 1, N) { a[i] = x; x += f[i]; }
	REP(i, 1, N) sumg[i] = (sumg[i - 1] + Get(a[i], a[i + 1] - 1) * i) % Mod;
	REP(i, 1, N) h[i] = (h[i - 1] + G(a[i + 1] - 1)) % Mod;
	while ( T -- )
	{
		int n; scanf("%lld", &n);
		printf("%lld\n", Solve(n));
	}
	return 0;
}
