/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年01月31日 星期日 09时15分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5e6 + 10;

int n, k, Mod, ans, r[maxn], f[maxn], g[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void NTT(int *a, int n, int inv)
{
    REP(i, 0, n - 1)     
    {
        r[i] = (r[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
        if ( r[i] > i ) swap(a[i], a[r[i]]);
    }
    for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
    {
        int tmp = power(3, (Mod - 1) / (Mid << 1));
        if ( inv == -1 ) tmp = power(tmp, Mod - 2);
        for ( int i = 0; i < n; i += (Mid << 1) ) 
        {
            int sum = 1;
            for ( int j = 0; j < Mid; ++ j, sum = sum * tmp % Mod )
            {
                int x = a[i + j], y = a[i + Mid + j] * sum % Mod;
                a[i + j] = (x + y) % Mod; a[i + Mid + j] = (x - y) % Mod;
            }
        }
    }
    if ( inv == -1 ) 
    {
        inv = power(n, Mod - 2);
        REP(i, 0, n - 1) a[i] = a[i] * inv % Mod;
    }
}

inline void Solve1(int l, int r)
{
    if ( l == r ) 
    {
		if ( l == 0 ) g[l] = 1;
        return ; 
    }
    int Mid = l + r >> 1, a[maxn], b[maxn];
    Solve1(l, Mid); 
    REP(i, 0, r - l) a[i] = b[i] = 0;
	REP(i, l, Mid) a[i - l] = g[i];
	REP(i, 0, r - l) b[i] = g[i];

	if ( l == 0 && r == 3 ) 
	{
		REP(i, 0, r - l) printf("%lld ", a[i]); puts("");
		REP(i, 0, r - l) printf("%lld ", b[i]); puts("");
	}

	NTT(a, r - l + 1, 1); NTT(b, r - l + 1, 1);
    REP(i, 0, r - l) a[i] = a[i] * b[i] % Mod;
    NTT(a, r - l + 1, -1);
	if ( l == 0 && r == 3 ) 
	{
		REP(i, 0, r - l) printf("%lld ", (a[i] + Mod) % Mod); puts("");
		REP(i, l, r) printf("%lld ", (g[i] + Mod) % Mod); puts("");
		puts("");
	}

	REP(i, Mid + 1, r) g[i] = (g[i] + a[i - l - 1] * (k - 1)) % Mod;
	/*
    REP(i, l, Mid) a[i - l] = (f[i] * sum1[i] % Mod) * power(fac[i], Mod - 2) % Mod;
    REP(i, 1, r - l) b[i - 1] = sum2[i] * power(fac[i], Mod - 2) % Mod;
    NTT(a, r - l + 1, 1); NTT(b, r - l + 1, 1);
    REP(i, 0, r - l) a[i] = a[i] * b[i] % Mod;
    NTT(a, r - l + 1, -1);
    REP(i, Mid + 1, r) f[i] = (f[i] + a[i - l - 1]) % Mod;
	*/
	Solve1(Mid + 1, r);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld", &n, &k, &Mod); n /= 2;
	int m = 1; while ( m <= n ) m <<= 1;
	Solve1(0, m - 1);
	f[0] = 1; //  g[0] = 1;
	REP(i, 0, m) printf("%lld ", (g[i] + Mod)% Mod); puts("");
	mem(g); g[0] = 1;
	REP(i, 1, n) REP(j, 1, i)
	{
		f[i] = (f[i] + f[i - j] * g[j - 1] * k) % Mod;
		if ( i == 3 ) cout << j << " " << g[i - j] * g[j - 1] * (k - 1) << endl;
		g[i] = (g[i] + g[i - j] * g[j - 1] * (k - 1)) % Mod;
	}
	REP(i, 0, n) printf("%lld ", g[i]); puts("");
	printf("%lld\n", (f[n] + Mod) % Mod);
    return 0;
}
