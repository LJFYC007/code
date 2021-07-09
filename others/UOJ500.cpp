/***************************************************************
	File name: UOJ500.cpp
	Author: ljfcnyali
	Create time: 2020年07月28日 星期二 16时16分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3e5 + 10;
const int maxm = 1 << 22;
const int Mod = 998244353;

int n, Q, a[maxn], q0, qx, qy, fac[maxn], inv[maxn], R[maxm], p[maxn];
LL ans;
vector<int> b, A, B;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = (LL)r * a % Mod; a = (LL)a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : ((LL)fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

unsigned long long NTTtmp[maxm];

inline vector<int> NTT(vector<int> a, int inv)
{
    int n = a.size();
	if (inv < 0) reverse(a.begin() + 1, a.end());
	static int *w[30], pool[maxm << 1 | 10];
	static bool vis[30];
	w[0] = pool;
	REP(i, 0, n - 1)
	{
		R[i] = (R[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
		if (i < R[i]) swap(a[i], a[R[i]]);
	}
	REP(i, 0, n - 1) NTTtmp[i] = (a[i] + Mod) % Mod;
	bool fff = (inv > 0);
	for (int i = 1, ccc = 0; i < n; i <<= 1, ccc++)
	{
		if (!vis[ccc])
		{
			vis[ccc] = 1;
			const LL wn = power(3, (Mod - 1) >> ccc + 1);
			if (i < maxm) w[ccc + 1] = w[ccc] + i;
			w[ccc][0] = 1;
			REP(j, 1, i - 1) w[ccc][j] = w[ccc][j - 1] * wn % Mod;
		}
		for (int k = 0; k < n; k += i + i)
			for (int l = 0; l < i; l++)
			{
				unsigned long long x(NTTtmp[k + l]), y(NTTtmp[k + l + i] * w[ccc][l] % Mod);
				NTTtmp[k + l] = x + y;
				NTTtmp[k + l + i] = Mod + x - y;
			}
	}
	REP(i, 0, n - 1) a[i] = NTTtmp[i] % Mod;
	if (inv < 0)
	{
		const int invn = power(n, Mod - 2);
		REP(i, 0, n - 1) a[i] = (LL)a[i] * invn % Mod;
	}
    return a;
}

vector<int> operator * (vector<int> a, vector<int> b)
{
    int n = a.size(), m = b.size(), len = 1;
    while ( len < n + m ) len <<= 1; a.resize(len); b.resize(len);
    a = NTT(a, 1); b = NTT(b, 1); REP(i, 0, len - 1) a[i] = (LL)a[i] * b[i] % Mod; a = NTT(a, -1);
    a.resize(n + m - 1); return a;
}

inline int Get(int x) { return ((LL)x * (x - 1) / 2) % (Mod - 1); }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = (LL)fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = (LL)inv[i + 1] * (i + 1) % Mod;
    scanf("%d%d", &n, &Q);
    REP(i, 0, n) scanf("%d", &a[i]);
    scanf("%d%d%d", &q0, &qx, &qy);

    int x = (LL)qy * power(1 - qx, Mod - 2) % Mod, invqx = power(qx, Mod - 2);
    REP(i, 0, n) p[i] = power(invqx, Get(i));

    A.resize(n + 1); B.resize(n + 1);
    REP(i, 0, n)
    {
        A[i] = (LL)fac[n - i] * a[n - i] % Mod;
        B[i] = (LL)power(x, i) * inv[i] % Mod;
    }
    b = A * B;
    REP(i, 0, n) if ( i < n - i ) swap(b[i], b[n - i]);
    REP(i, 0, n) b[i] = ((LL)b[i] * power(q0 - x, i) % Mod) * inv[i] % Mod;

    A.clear(); A.resize(n + Q + 1); B.resize(n + Q + 1); 
    REP(i, 0, n + Q) B[i] = power(qx, Get(i));
    REP(i, 0, n) A[i] = (LL)b[i] * p[i] % Mod;
    reverse(A.begin(), A.begin() + n + 1);
    b = A * B;

    REP(i, 1, Q) 
        if ( i <= n ) ans ^= (((LL)b[n + i] * p[i] % Mod) + Mod) % Mod;
        else ans ^= (((LL)b[n + i] * power(invqx, Get(i)) % Mod) + Mod) % Mod;
    printf("%lld\n", ans);
    return 0;
}
