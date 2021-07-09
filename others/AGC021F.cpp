/***************************************************************
	File name: AGC021F.cpp
	Author: ljfcnyali
	Create time: 2021年06月24日 星期四 11时21分23秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 8010;
const int Mod = 998244353;

int n, m, f[maxn][210], fac[maxn], inv[maxn], ans, r[maxn << 2];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int C(int n, int m) { return n < m ? 0 : fac[n] * inv[m] % Mod * inv[n - m] % Mod; } 

inline void NTT(vector<int> &f, int inv)
{
	int n = f.size(); 
	REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
	REP(i, 0, n - 1) if ( i < r[i] ) swap(f[i], f[r[i]]);
    for ( int Mid = 1; Mid < n; Mid <<= 1 )
    {
        int tmp = power(3, (Mod - 1) / (Mid << 1));
        if ( inv == -1 ) tmp = power(tmp, Mod - 2);
        for ( int i = 0; i < n; i += (Mid << 1) )
        {
            int sum = 1;
            for ( int j = 0; j < Mid; ++ j, sum = (sum * tmp) % Mod )
            {
                int x = f[i + j], y = (sum * f[i + j + Mid]) % Mod;
                f[i + j] = (x + y) % Mod; f[i + j + Mid] = (x - y + Mod) % Mod;
            }
        }
    }
	if ( inv == -1 ) 
	{
		inv = power(n, Mod - 2);
		REP(i, 0, n - 1) f[i] = f[i] * inv % Mod;
	}
}

vector<int> operator *(vector<int> a, vector<int> b)
{
	int n = a.size(), m = b.size(), len = 1;
	while ( len < n + m - 1 ) len <<= 1; a.resize(len); b.resize(len);
	NTT(a, 1); NTT(b, 1); REP(i, 0, len - 1) a[i] = a[i] * b[i] % Mod; NTT(a, -1);
	a.resize(n + m - 1); return a;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	n = maxn - 1; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	scanf("%lld%lld", &n, &m); 
	f[0][0] = 1;
	REP(j, 1, m) 
	{
		vector<int> a(n + 1), b(n + 1);
		REP(i, 0, n) a[i] = f[i][j - 1] * inv[i] % Mod;
		REP(i, 1, n) b[i] = inv[i + 2];
		a = a * b;
		REP(i, 0, n) f[i][j] = (f[i][j - 1] * (1 + i + C(i, 2)) + a[i] * fac[i + 2]) % Mod;
	}
	REP(i, 0, n) ans = (ans + C(n, i) * f[i][m]) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
