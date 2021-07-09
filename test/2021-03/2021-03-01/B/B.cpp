#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
 
const int maxn = 4e5 + 10;
const int Mod = 998244353;
 
int n, k, m, fac[maxn], inv[maxn], r[maxn], ans, t[maxn];
 
inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int sgn(int x) { return x & 1 ? -1 : 1; } 
inline int C(int n, int m) { return n < m ? 0 : fac[n] * inv[m] % Mod * inv[n - m] % Mod; } 
inline int add(int x, int y) { return x + y >= Mod ? x + y - Mod : x + y; } 
int buf[maxn]; 
inline void NTT(vector<int> &f, int n, int inv)
{
	REP(i, 0, n - 1) f[i] = f[i] < 0 ? f[i] + Mod : f[i];
    REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    REP(i, 0, n - 1) if ( i < r[i] ) swap(f[i], f[r[i]]);
	buf[0]=1;
    for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
    {
        int tmp = power(3, (Mod - 1) / (Mid << 1));
        if ( inv == -1 ) tmp = power(tmp, Mod - 2); 
		for(int i=Mid;i>0;i-=2)buf[i]=buf[i>>1];
		for(int i=1;i<Mid;i+=2)buf[i]=buf[i-1]*tmp%Mod;
        for ( int i = 0; i < n; i += (Mid << 1) ) 
        {
            int sum = 1;
            for ( int j = 0; j < Mid; ++ j) 
            {
                int x = f[i + j], y = f[i + Mid + j] * buf[j] % Mod;
				f[i + j] = x+y; f[i + Mid + j] = x + Mod - y;
            }
        }
		if(Mid==(1<<8)){
			for(int i=0;i<n;++i)f[i]%=Mod;
		}
		if(Mid==(1<<16)){
			for(int i=0;i<n;++i)f[i]%=Mod;
		}
    }
	for(int i=0;i<n;++i)if(f[i]>=Mod)f[i]%=Mod;
    if ( inv == -1 ) 
    {
        inv = power(n, Mod - 2); 
        REP(i, 0, n - 1) f[i] = f[i] * inv % Mod;
    }
}

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
    int n = a.size(), m = b.size(), l = 1;
	if ( n + m <= 16 ) 
	{
		vector<int> c(n + m - 1);
		REP(i, 0, n - 1) REP(j, 0, m - 1) c[i + j] += a[i] * b[j];
		REP(i, 0, n + m - 1) c[i] %= Mod;
		return c;
	}
    while ( l < n + m - 1 ) l <<= 1; a.resize(l); b.resize(l);
    NTT(a, l, 1); NTT(b, l, 1); REP(i, 0, l - 1) a[i] = a[i] * b[i] % Mod; NTT(a, l, -1);
    a.resize(n + m - 1); return a;
}

inline void Solve(int l, int r, vector<int> &f, vector<int> &g, vector<int> &h)
{
	if ( l == r ) 
	{ 
		if ( l >= n ) return ;
		f.resize(2); f[1] = -t[l]; f[0] = t[l] - n;
		g.resize(2); g[1] = -1 - t[l]; g[0] = (1 + t[l] - n) % Mod;
		return ; 
	}
	vector<int> a(1), b(1), c(1); a[0] = b[0] = c[0] = 1;
	vector<int> x(1), y(1), z(1); x[0] = y[0] = z[0] = 1;
	int Mid = l + r >> 1; Solve(l, Mid, a, b, c); Solve(Mid + 1, r, x, y, z);
	f = a * x; g = b * y; h = a * z + c * y;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &k, &m);
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	REP(i, 1, n - 1) t[i] = n - i - (i >= k);
	vector<int> f(1), g(1), h(1); f[0] = g[0] = h[0] = 1;
	Solve(1, n, f, g, h); ans = h[m] * sgn(n - 1) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
