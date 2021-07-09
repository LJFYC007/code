/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2021年03月11日 星期四 17时11分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int MOD = 998244353;

int k, Mod, ans, r[maxn], g[maxn], buf[maxn];
LL m;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int power(LL a, int b, int Mod) { LL r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int add(int x, int y) { return x + y >= Mod ? x + y - Mod : x + y; } 

inline int sgn(int x) { return x & 1 ? -1 : 1; } 

inline void NTT(vector<int> &a, int inv)
{
	int n = a.size(); vector<unsigned long long> f(n); 
	REP(i, 0, n - 1) f[i] = a[i];
    REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    REP(i, 0, n - 1) if ( i < r[i] ) swap(f[i], f[r[i]]);
	buf[0]=1;
    for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
    {
        int tmp = power(3, (MOD - 1) / (Mid << 1), MOD);
        if ( inv == -1 ) tmp = power(tmp, MOD - 2, MOD); 
		for(int i=Mid;i>0;i-=2)buf[i]=buf[i>>1];
		for(int i=1;i<Mid;i+=2)buf[i]=1ll * buf[i-1]*tmp%MOD;
        for ( int i = 0; i < n; i += (Mid << 1) ) 
        {
            int sum = 1;
            for ( int j = 0; j < Mid; ++ j) 
            {
                unsigned long long x = f[i + j], y = f[i + Mid + j] * buf[j] % MOD;
				f[i + j] = x + y; f[i + Mid + j] = x + MOD - y;
            }
        }
    }
	REP(i, 0, n - 1) f[i] %= MOD;
    if ( inv == -1 ) 
    {
        inv = power(n, MOD - 2, MOD); 
        REP(i, 0, n - 1) f[i] = f[i] * inv % MOD;
    }
	REP(i, 0, n - 1) a[i] = f[i] % MOD;
}

inline vector<int> operator * (vector<int> a, vector<int> b)
{
	int n = a.size(), m = b.size(), len = 1; 
	REP(i, 0, n - 1) a[i] = (a[i] + Mod) % Mod;
	REP(i, 0, m - 1) b[i] = (b[i] + Mod) % Mod;
	while ( len < n + m - 1 ) len <<= 1; a.resize(len); b.resize(len);
	NTT(a, 1); NTT(b, 1); REP(i, 0, len - 1) a[i] = 1ll * a[i] * b[i] % MOD; NTT(a, -1);
	a.resize(n + m - 1); REP(i, 0, n + m - 2) a[i] = a[i] % Mod; return a;
}

inline vector<int> Mul(vector<int> a, vector<int> b)
{
	a = a * b; if ( a.size() < k ) a.resize(k); 
	int n = a.size(), sum = 0; REP(i, 0, n - 1) g[i] = 0;
	while ( n > k ) 
	{ 
		sum = add(sum, g[n - 1]);
		int x = add(a[n - 1], sum);
		g[n - 2] = add(g[n - 2], x);
		if ( n - k - 2 >= 0 ) g[n - k - 2] = add(g[n - k - 2], Mod - x);
		-- n; 
	}
	a.resize(k);
	for ( int i = k - 1; i >= 0; -- i ) { sum = add(sum, g[i]); a[i] = add(a[i], sum); }
	return a;
}

inline vector<int> Get(LL b)
{
	vector<int> a(2), r(1, 1); a[1] = 1; a = Mul(r, a);
	while ( b ) { if ( b & 1 ) r = Mul(r, a); a = Mul(a, a); b >>= 1; }
	return r;
}

inline int Solve(LL m)
{
	vector<int> f = Get(m); int ret = 0;
	for ( int i = 0; i < f.size(); ++ i ) ret = (ret + f[i] * (i >= 1 ? power(2, i - 1) : 1)) % Mod;	
	return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	cin >> k >> m >> Mod;
	if ( k == 1 ) { puts("1"); return 0; } 
	ans = (Solve(m + 1) - Solve(m - k + 1)) % Mod;
	printf("%d\n", (ans + Mod) % Mod);
    return 0;
}
