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

int n, m, Begin[maxn], Next[maxn], To[maxn], e, f[maxn], dis[maxn];
int fac[maxn], inv[maxn], a[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u)
{
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == f[u] ) continue ;
		f[v] = u; dis[v] = dis[u] + 1; DFS(v);
	}
}

inline int A(int n, int m) { return n < m ? 0 : fac[n] * inv[n - m] % Mod; }

inline int Solve()
{
	if ( m == 1 ) return (fac[a[1] - 1] + fac[a[1] - 2]) % Mod;
	int ret = A(a[1], a[1]), sum = a[1] + 1;
	REP(i, 2, m - 1)
	{
		ret = ret * A(sum + a[i], a[i]) % Mod;
		sum += a[i] + 1;
	}
	ret = ret * (A(sum + a[m], a[m]) + A(sum + a[m] - 1, a[m] - 1)) % Mod;
	return ret;
}

inline void read(int &x)
{
	char c = getchar(); x = 0;
	while ( c < '0' || c > '9' ) c = getchar();
	while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
	freopen("track.in", "r", stdin);
	freopen("track.out", "w", stdout);
	scanf("%lld", &n);
	REP(i, 1, n - 1) { int u, v; read(u); read(v); add(u, v); add(v, u); }
	int N = n * 2;
	fac[0] = inv[0] = 1; REP(i, 1, N) fac[i] = fac[i - 1] * i % Mod;
	inv[N] = power(fac[N], Mod - 2); for ( int i = N - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	int x = 1; DFS(1);
	REP(i, 1, n) if ( dis[i] > dis[x] ) x = i;
	mem(f); mem(dis); DFS(x);
	REP(i, 1, n) if ( dis[i] > dis[x] ) x = i;
	x = f[x];
	while ( f[x] )
	{
		a[++ m] = -2;
		for ( int i = Begin[x]; i; i = Next[i] ) ++ a[m];
		x = f[x];
	}
	++ a[1]; ++ a[m];
	int sum = 0;
	REP(i, 1, m) sum += a[i] + 1;
	if ( sum != n ) { puts("0"); return 0; }
	int ans = Solve();
	bool flag = false;
	REP(i, 1, m) if ( a[i] != a[m - i + 1] ) flag = true;
	reverse(a + 1, a + m + 1);
	if ( flag == true ) ans = (ans + Solve()) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}
