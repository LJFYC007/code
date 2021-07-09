/***************************************************************
	File name: sum.cpp
	Author: ljfcnyali
	Create time: 2020年07月08日 星期三 15时03分03秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;
const int Mod = 998244353;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

int r[maxn], invs[maxn];

inline vector<int> NTT(vector<int> a, int inv)
{
    int n = a.size();
    static vector<int> w[30][2];
    vector<unsigned long long> f(n); 
    REP(i, 0, n - 1) f[i] = (a[i] + Mod) % Mod;
    REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    REP(i, 0, n - 1) if ( r[i] < i ) swap(f[r[i]], f[i]);
    bool fff = inv == 1;
    for ( int Mid = 1, ccc = 0; Mid < n; Mid <<= 1, ++ ccc ) 
    {
        if (!w[ccc][1].size())
		{
			const int wn = power(3, (Mod - 1) >> ccc + 1), Invwn = power(wn, Mod - 2);
			w[ccc][0].push_back(1);
			w[ccc][1].push_back(1);
			REP(j, 1, Mid - 1)
			{
				w[ccc][0].push_back(w[ccc][0].back() * Invwn % Mod);
				w[ccc][1].push_back(w[ccc][1].back() * wn % Mod);
			}
		}
        for ( int i = 0; i < n; i += (Mid << 1) ) 
            REP(j, 0, Mid - 1)
            {
                int x = f[i + Mid + j] * w[ccc][fff][j] % Mod;
				f[i + Mid + j] = f[i + j] - x + Mod;
                f[i + j] += x;
            }
    }
    if ( inv == -1 ) 
    {
        inv = power(n, Mod - 2);
        REP(i, 0, n - 1) f[i] = f[i] * inv % Mod;
    }
    REP(i, 0, n - 1) a[i] = f[i] % Mod; return a;
}

inline vector<int> Mul(vector<int> a, vector<int> b)
{
    int n = a.size(), m = b.size(), len = 1;
    while ( len <= n + m ) len <<= 1;
    a.resize(len); b.resize(len);
    a = NTT(a, 1); b = NTT(b, 1);
    REP(i, 0, len - 1) a[i] = a[i] * b[i] % Mod;
    a = NTT(a, -1); a.resize(n + m); return a;
}

inline vector<int> Inv(vector<int> f)
{
    vector<int> g, h;
    if ( f.size() == 1 ) { g.resize(1); g[0] = power(f[0], Mod - 2); return g; }
    int n = f.size(); g = f; g.resize((n + 1) / 2); g = Inv(g);
    h = Mul(f, g); REP(i, 0, n - 1) h[i] = Mod - h[i]; h[0] += 2;
    f = Mul(h, g); f.resize(n); return f;
}

inline vector<int> ln(vector<int> f)
{
    vector<int> g = f; int n = f.size();
    REP(i, 0, n - 2) f[i] = f[i + 1] * (i + 1) % Mod; f.resize(n - 1);
    g = Inv(g); f = Mul(g, f); f.resize(n);
    for ( int i = n - 1; i >= 1; -- i ) f[i] = f[i - 1] * invs[i] % Mod;
    f[0] = 0; return f;
}

inline vector<int> exp(vector<int> f)
{
    vector<int> g, h;
    if ( f.size() == 1 ) { g.resize(1); g[0] = 1; return g; }
    int n = f.size(); g = f; g.resize((n + 1) / 2); g = exp(g); g.resize(n);
    h = ln(g); REP(i, 0, n - 1) f[i] = f[i] >= h[i] ? f[i] - h[i] : f[i] - h[i] + Mod; ++ f[0];
    f = Mul(f, g); f.resize(n); return f;
}

inline vector<int> power(vector<int> f, int n)
{
    int x = f[0], y = power(x, Mod - 2), len = f.size(); n %= Mod;
    REP(i, 0, len - 1) f[i] = f[i] * y % Mod; f = ln(f);
    REP(i, 0, len - 1) f[i] = f[i] * n % Mod; f = exp(f); 
    y = power(x, n); REP(i, 0, len - 1) f[i] = f[i] * y % Mod;
    return f;
}

int S, T, N, M, n = 1;
vector<int> f, g;

signed main()
{
    freopen("sum.in", "r", stdin);
    freopen("sum.out", "w", stdout);
    scanf("%lld%lld%lld%lld", &S, &T, &N, &M);
    while ( n <= M - N ) n <<= 1;
    if ( N <= 1000000 && n <= N ) n <<= 1;
    invs[0] = invs[1] = 1;
    REP(i, 2, n) invs[i] = invs[Mod % i] * (Mod - Mod / i) % Mod;
    f.resize(n); f[0] = f[1] = 1; f = power(f, T); 
    REP(i, 1, n - 1) f[i - 1] = f[i]; f[n - 1] = 0; f.resize(n); f = power(f, N);
    g.clear(); g.resize(n); g[0] = g[1] = 1; g = power(g, S - N * T);
    f = Mul(f, g); printf("%lld\n", (f[M - N] + Mod) % Mod);
    return 0;
}
