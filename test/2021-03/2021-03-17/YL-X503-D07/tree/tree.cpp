#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 4e5 + 10;
const int Mod = 998244353;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, r[maxn], son[maxn], dis[maxn];
int size[maxn], fa[maxn], buf[maxn];
vector<int> f[maxn], a[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline int power(int a, int b, int Mod) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

inline void NTT(vector<int> &a, int inv)
{
    int n = a.size(); vector<unsigned long long> f(n); 
    REP(i, 0, n - 1) f[i] = a[i];
    REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    REP(i, 0, n - 1) if ( i < r[i] ) swap(f[i], f[r[i]]);
    buf[0]=1;
    for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
    {
        int tmp = power(3, (Mod - 1) / (Mid << 1), Mod);
        if ( inv == -1 ) tmp = power(tmp, Mod - 2, Mod); 
        for(int i=Mid;i>0;i-=2)buf[i]=buf[i>>1];
        for(int i=1;i<Mid;i+=2)buf[i]=1ll * buf[i-1]*tmp%Mod;
        for ( int i = 0; i < n; i += (Mid << 1) ) 
            for ( int j = 0; j < Mid; ++ j) 
            {
                unsigned long long x = f[i + j], y = f[i + Mid + j] * buf[j] % Mod;
                f[i + j] = (x + y) % Mod; f[i + Mid + j] = (x + Mod - y) % Mod;
            }
    }
    REP(i, 0, n - 1) f[i] %= Mod;
    if ( inv == -1 ) 
    {
        inv = power(n, Mod - 2, Mod); 
        REP(i, 0, n - 1) f[i] = f[i] * inv % Mod;
    }
    REP(i, 0, n - 1) a[i] = f[i] % Mod;
}
 
inline vector<int> operator + (vector<int> a, vector<int> b)
{
	int n = max(a.size(), b.size()); a.resize(n); b.resize(n);
	REP(i, 0, n - 1) a[i] = (a[i] + b[i]) % Mod;
	return a;
}
inline vector<int> operator * (vector<int> a, vector<int> b)
{
    int n = a.size(), m = b.size(), len = 1; 
	if ( n + m <= 16 ) 
	{
		vector<int> c(n + m - 1);
		REP(i, 0, n - 1) REP(j, 0, m - 1) c[i + j] += a[i] * b[j];
		REP(i, 0, n + m - 2) c[i] %= Mod; return c;
	}
    REP(i, 0, n - 1) a[i] = (a[i] + Mod) % Mod;
    REP(i, 0, m - 1) b[i] = (b[i] + Mod) % Mod;
    while ( len < n + m - 1 ) len <<= 1; a.resize(len); b.resize(len);
    NTT(a, 1); NTT(b, 1); REP(i, 0, len - 1) a[i] = 1ll * a[i] * b[i] % Mod; NTT(a, -1);
    a.resize(n + m - 1); return a;
}

inline vector<int> Solve(int l, int r)
{
	if ( l > r ) { vector<int> f(1, 0); return f; } 
	if ( l == r ) return a[l];
	int Mid = l + r >> 1; return Solve(l, Mid) * Solve(Mid + 1, r);
}

inline vector<int> calc(int l, int r)
{
	if ( l > r ) { vector<int> f(1, 0); return f; } 
	if ( l == r ) return a[l];
	int Mid = l + r >> 1; return calc(l, Mid) + calc(Mid + 1, r) * Solve(l, Mid);
}

inline void DFS1(int u)
{
	size[u] = 1;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; dis[v] = dis[u] + 1; DFS1(v); 
		size[u] += size[v]; if ( size[v] > size[son[u]] ) son[u] = v;
	}
}

inline void DFS2(int u)
{
	for ( int i = Begin[u]; i; i = Next[i] ) DFS2(To[i]);
	m = 0; for ( int i = Begin[u]; i; i = Next[i] ) if ( To[i] != son[u] ) a[++ m] = f[To[i]];
	f[u] = Solve(1, m); if ( f[u].size() == 1 ) f[u][0] = 1;
	if ( son[fa[u]] != u ) 
	{
		m = 0; int x = u; a[++ m] = f[x];
		while ( son[x] ) { x = son[x]; a[++ m] = f[x]; } 
		vector<int> g(2); g[0] = 0; g[1] = 1; a[m][0] = 0;
		f[u] = calc(1, m - 1) * g + Solve(1, m); ++ f[u][1];
		f[u][0] = 0;
	}
}

signed main()
{
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	scanf("%lld", &n); 
	REP(i, 2, n) { scanf("%lld", &fa[i]); add(fa[i], i); }
	dis[1] = 1; DFS1(1); DFS2(1);
	int ans = 0, x = 1; f[1].resize(n + 1);
	REP(i, 1, n) { x = x * i % Mod; int y; scanf("%lld", &y); ans = (ans + y * f[1][i] % Mod * x) % Mod; }
	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}
