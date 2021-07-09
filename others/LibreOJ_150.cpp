/***************************************************************
	File name: LibreOJ_150.cpp
	Author: ljfcnyali
	Create time: 2021年04月09日 星期五 08时57分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 998244353;

int n, r[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

inline void NTT(vector<int> &f, int inv)
{
	int n = f.size(); REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
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
				int x = f[i + j], y = sum * f[i + Mid + j] % Mod;
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

inline vector<int> operator *(vector<int> a, vector<int> b)
{
	int n = a.size(), m = b.size(), len = 1;
	while ( len < n + m ) len <<= 1; a.resize(len); b.resize(len);
	NTT(a, 1); NTT(b, 1); REP(i, 0, len - 1) a[i] = a[i] * b[i] % Mod; NTT(a, -1);
	a.resize(n + m - 1); return a;
}

inline vector<int> Inv(vector<int> f)
{
	int n = f.size();
	if ( n == 1 ) { f[0] = power(f[0], Mod - 2); return f; } 
	vector<int> g = f; g.resize((n + 1) / 2); g = Inv(g); g.resize(n);
	vector<int> h = f * g; h.resize(n); REP(i, 0, n - 1) h[i] = -h[i]; h[0] += 2;
	h = h * g; h.resize(n); return h;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	vector<int> f(n); REP(i, 0, n - 1) scanf("%lld", &f[i]);
	vector<int> g = Inv(f); REP(i, 0, n - 1) printf("%lld ", (g[i] + Mod) % Mod); puts("");
    return 0;
}
