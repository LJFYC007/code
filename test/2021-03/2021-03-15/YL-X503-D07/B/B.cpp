#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 20010;
const int Mod = 998244353;

int n, m, a[maxn], b[maxn], fac[maxn], inv[maxn], ans, f[maxn], buf[maxn], r[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = 1ll * r * a % Mod; a = 1ll * a * a % Mod; b >>= 1; } return r; } 
inline int C(int n, int m) { return n < m ? 0 : 1ll * fac[n] * inv[m] % Mod * inv[n - m] % Mod; }
inline int sgn(int x) { return x & 1 ? -1 : 1; } 

inline void NTT(vector<int> &a, int inv)
{
	int n = a.size(); vector<unsigned long long> f(n); 
    REP(i, 0, n - 1) f[i] = (a[i] + Mod) % Mod;
    REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    REP(i, 0, n - 1) if ( i < r[i] ) swap(f[i], f[r[i]]);
    buf[0]=1;
    for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
    {
        int tmp = power(3, (Mod - 1) / (Mid << 1));
        if ( inv == -1 ) tmp = power(tmp, Mod - 2); 
        for(int i=Mid;i>0;i-=2)buf[i]=buf[i>>1];
        for(int i=1;i<Mid;i+=2)buf[i]=1ll * buf[i-1]*tmp%Mod;
        for ( int i = 0; i < n; i += (Mid << 1) ) 
            for ( int j = 0; j < Mid; ++ j) 
            {
                unsigned long long x = f[i + j], y = f[i + Mid + j] * buf[j] % Mod;
                f[i + j] = x + y; f[i + Mid + j] = x + Mod - y;
            }
    }
    REP(i, 0, n - 1) f[i] %= Mod;
    if ( inv == -1 ) 
    {
        inv = power(n, Mod - 2); 
        REP(i, 0, n - 1) f[i] = f[i] * inv % Mod;
    }
    REP(i, 0, n - 1) a[i] = f[i];
}

inline vector<int> operator *(vector<int> a, vector<int> b)
{
	int n = a.size(), m = b.size(), len = 1;
	while ( len < n + m - 1 ) len <<= 1; a.resize(len); b.resize(len);
	NTT(a, 1); NTT(b, 1); REP(i, 0, len - 1) a[i] = 1ll * a[i] * b[i] % Mod; NTT(a, -1);
	return a;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = 1ll * fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = 1ll * inv[i + 1] * (i + 1) % Mod;
	scanf("%d%d", &n, &m);
	REP(i, 1, m) scanf("%d", &a[i]);
	sort(a + 1, a + m + 1);
	while ( n -- ) 
	{
		int op; scanf("%d", &op); REP(i, 1, m) scanf("%d", &b[i]); sort(b + 1, b + m + 1);

		if ( op == 1 ) 
		{
			int l = 1, r = m, ans = 0;
			for ( int i = m; i >= 1; -- i ) 
				if ( a[r] > b[i] ) { -- r; ++ ans; } 
				else ++ l;
			if ( ans >= (m + 1) / 2 ) puts("1");
			else puts("0");
			continue ; 
		}

		REP(i, 1, m) b[i] = lower_bound(a + 1, a + m + 1, b[i]) - a;
		
		f[0] = 1; REP(i, 1, m) f[i] = 0;
		REP(i, 1, m)
		{
			int x = m - b[m - i + 1] + 1;
			for ( int j = x; j >= 1; -- j ) f[j] = (f[j] + 1ll * f[j - 1] * (x - j + 1)) % Mod;
		}

		vector<int> a(m + 1), b(m + 1); 
		REP(i, 0, m) a[m - i] = 1ll * f[i] * fac[m - i] % Mod * fac[i] % Mod;
		REP(i, 0, m) b[i] = inv[i] * sgn(i);
		a = a * b;
		int ans = 0; REP(i, (m + 1) / 2, m) ans = (ans + 1ll * a[m - i] * inv[i]) % Mod;
		ans = 1ll * ans * inv[m] % Mod;
		printf("%d\n", (ans + Mod) % Mod);
	}
	return 0;
}
