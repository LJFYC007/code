#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 1e6 + 10;
const int Mod = 1e9 + 7;

int n, L, X, Y, K, fac[maxn], inv[maxn], ans;
struct Matrix { int n, m, a[20][20]; } ;
Matrix operator *(Matrix a, Matrix b)
{
	Matrix c; c.n = a.n; c.m = b.m;
	REP(i, 1, c.n) REP(j, 1, c.m) c.a[i][j] = 0;
	REP(i, 1, c.n) REP(j, 1, c.m) REP(k, 1, a.m) c.a[i][j] = (c.a[i][j] + a.a[i][k] * b.a[k][j]) % Mod;
	return c;
}

inline Matrix power(Matrix a, int b)
{
	Matrix r = a; -- b;
	while ( b ) { if ( b & 1 ) r = r * a; a = a * a; b >>= 1; } 
	return r;
}

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int sgn(int x) { return x & 1 ? -1 : 1; } 

vector<int> operator +(vector<int> a, vector<int> b)
{
    int n = max(a.size(), b.size()); a.resize(n); b.resize(n);
    REP(i, 0, n - 1) a[i] = (a[i] + b[i]) % Mod; return a;
}
vector<int> operator -(vector<int> a, vector<int> b)
{
    int n = max(a.size(), b.size()); a.resize(n); b.resize(n);
    REP(i, 0, n - 1) a[i] = (a[i] - b[i]) % Mod; return a;
}
vector<int> operator *(vector<int> a, vector<int> b)
{
	int n = a.size(), m = b.size(); vector<int> c(n + m - 1);
	REP(i, 0, n - 1) REP(j, 0, m - 1) c[i + j] = (c[i + j] + a[i] * b[j]) % Mod;;
	return c;
}
vector<pii> operator *(vector<pii> a, vector<pii> b)
{
	vector<pii> c, d;
	for ( auto x : a ) for ( auto y : b ) c.push_back(pii(x.first + y.first, x.second * y.second % Mod));
	sort(c.begin(), c.end()); int m = 0;
	for ( int i = 0; i < c.size(); ++ i ) 
		if ( !m || d[m - 1].first != c[i].first ) { d.push_back(c[i]); ++ m; }
		else d[m - 1].second = (d[m - 1].second + c[i].second) % Mod;
	return d;
}

inline vector<int> ln(vector<int> g)
{
	int n = g.size(); vector<int> f(n); f[0] = 0;
	REP(k, 0, n - 2)
	{
		int ret = g[k + 1] * (k + 1) % Mod;
		REP(i, 0, k - 1) ret = (ret - g[k - i] * f[i + 1] % Mod * (i + 1)) % Mod;
		f[k + 1] = ret * power(k + 1, Mod - 2) % Mod;
	}
	return f;
}

inline int Inv(vector<int> g, int n)
{
	int m = g.size(); vector<int> f(m);
	REP(i, 1, m - 1) g[i] = -g[i] * power(g[0], Mod - 2) % Mod;
	f[0] = 1; REP(i, 1, m - 1) REP(j, 1, m - 1) if ( i >= j ) f[i] = (f[i] + f[i - j] * g[j]) % Mod;
	if ( n < m ) return f[n] * power(g[0], Mod - 2) % Mod;

	Matrix a, b; -- m; a.n = a.m = m;
	REP(i, 1, m) REP(j, 1, m) a.a[i][j] = 0; REP(i, 2, m) a.a[i][i - 1] = 1; REP(i, 1, m) a.a[1][i] = g[i];
	b.n = m; b.m = 1; REP(i, 1, m) b.a[i][1] = f[m - i + 1];
	b = power(a, n - m) * b;
	return b.a[1][1] * power(g[0], Mod - 2) % Mod;
}

inline int Get(vector<pii> a, vector<int> b, int n)
{
	int ret = 0; 
	for ( auto it : a ) if ( it.first <= n ) ret = (ret + it.second * Inv(b, n - it.first)) % Mod;
	return ret;	
}

inline void Solve(int x, vector<pii> a, vector<int> b)
{
	for ( int i = 0; i < b.size(); ++ i ) b[i] = b[i] * x % Mod;
	vector<int> c(2); c[0] = 1; c[1] = -1; b = b * c * c;
	ans = (ans + Get(a, b, Y - 1) - Get(a, b, L)) % Mod;
}

inline void DFS(int num, int sum, vector<pii> a, vector<int> b, int ret)
{
	if ( !num ) 
	{ 
		Solve(fac[sum], a, b); 
		ans = (ans + ret * inv[sum] % Mod * (L - Y + 1)) % Mod; 
		return ; 
	} 
	REP(i, 1, n - 1)
	{
		if ( num < i ) continue ; 
		vector<pii> c(2); c[0] = pii(0, 1); c[1] = pii(i * (X + 1), -1);
		vector<int> d(i + 1); d[0] = i; d[i] = -i;
		DFS(num - i, sum + 1, a * c, b * d, ret * power(i, Mod - 2) % Mod * (X + 1) % Mod);
	}
	REP(i, 1, n - 1)
	{
		int j = i * (K + 1);
		if ( num < j ) continue ; 
		vector<pii> c(2); c[0] = pii(0, -1); c[1] = pii(j * (X + 1), 1);
		vector<int> d(j + 1); d[0] = i; d[j] = -i;
		DFS(num - j, sum + 1, a * c, b * d, -ret * power(i, Mod - 2) % Mod * (X + 1) % Mod);
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	cin >> n >> L >> Y >> X >> K; K = min(K, n - 1);
	fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;

	vector<pii> a(1, pii(0, 1)); vector<int> b(1, 1);
	DFS(n - 1, 0, a, b, 1); 
	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}
