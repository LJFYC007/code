#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 0x3f3f3f3f;
const int Mod = 998244353;

int r[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void NTT(int *f, int n, int inv)
{
	REP(i, 1, n - 1) r[i] = (r[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
	REP(i, 0, n - 1) if ( i < r[i] ) swap(f[i], f[r[i]]);
	for ( int Mid = 1; Mid < n; Mid <<= 1 )
	{
		int tmp = power(3, (Mod - 1) / (Mid << 1));
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

int n, m, Begin[maxn], Next[maxn], To[maxn], e, a[maxn], ans[maxn];
int size[maxn], Root, Max, N, f[maxn], g[maxn], A[maxn], B[maxn];
bool use[maxn];
vector<int> t1[maxn], t2[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
	size[u] = 1; int x = 0;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa || use[v] ) continue ;
		DFS1(v, u); size[u] += size[v];
		x = max(x, size[v]);
	}
	x = max(x, N - size[u]);
	if ( x < Max ) { Max = x; Root = u; }
}

inline void DFS2(int u, int fa, int Max, int Min, int sum1, int sum2, int num1, int num2)
{
	if ( fa != 0 )
	{
		sum1 += a[u]; sum2 += a[u];
		if ( sum1 > Max ) { Max = sum1; num1 = 0; }
		if ( sum1 == Max ) { ++ num1; t1[Max].push_back(u); f[u] = num1; }
		if ( sum2 < Min ) { Min = sum2; num2 = 0; }
		if ( sum2 == Min ) { ++ num2; t2[-Min].push_back(u); g[u] = num2; }
	}
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa || use[v] ) continue ;
		DFS2(v, u, Max, Min, sum1, sum2, num1, num2);
	}
}

inline void DFS3(int u, int fa)
{
	++ N;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa || use[v] ) continue ;
		DFS3(v, u);
	}
}

inline void Solve(int u)
{
	REP(i, 0, N) { t1[i].clear(); t2[i].clear(); }
	if ( a[u] == 1 ) { t1[1].push_back(u); f[u] = 1; }
	DFS2(u, 0, a[u], 0, a[u], 0, 1, 1);
	REP(i, 0, N)
	{
		int x = max(t1[i].size(), t2[i].size());
		int len = 1;
		while ( len < (x << 1) ) len <<= 1;
		REP(j, 0, len - 1) A[j] = B[j] = 0;
		if ( t1[i].size() ) REP(j, 0, t1[i].size() - 1) ++ A[f[t1[i][j]] - 1];
		if ( t2[i].size() ) REP(j, 0, t2[i].size() - 1) ++ B[g[t2[i][j]] - 1];
		if ( i == 0 ) B[0] = 1;
		NTT(A, len, 1); NTT(B, len, 1);
		REP(j, 0, len - 1) A[j] = A[j] * B[j] % Mod;
		NTT(A, len, -1);
		if ( t1[i].size()) {REP(j, 0, t1[i].size() - 1) printf("%d ", t1[i][j]); puts("");}
		if ( t2[i].size()) {REP(j, 0, t2[i].size() - 1) printf("%d ", t2[i][j]); puts("");}
		if ( t1[i].size()&&t2[i].size()) {REP(j, 0, len - 1) printf("%d ", A[j]); puts(""); }
		REP(j, 0, len - 1) ans[j] += (A[j] + Mod) %Mod;
	}
	use[u] = true;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( use[v] ) continue ;
		N = 0; DFS3(v, 0); Max = N; Root = v;
		DFS1(Root, 0); Solve(Root);
	}
}

signed main()
{
	freopen("bracket.in", "r", stdin);
	freopen("bracket.out", "w", stdout);
	scanf("%lld", &n);
	REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
	REP(i, 1, n) { char c; getchar(); scanf("%c", &c); a[i] = c == '(' ? 1 : -1; }
	Root = 1; Max = N = n; DFS1(Root, 0); Solve(Root);
	scanf("%lld", &m);
	REP(i, 1, m) { int x; scanf("%lld", &x); printf("%lld\n", ans[x]); }
	return 0;
}
