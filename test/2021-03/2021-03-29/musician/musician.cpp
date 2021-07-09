#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 4e6 + 10;
const int Mod = 998244353;

int n, N, a[maxn], b[maxn], ans, f[maxn], r[maxn], buf[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = 1ll * r * a % Mod; a = 1ll * a * a % Mod; b >>= 1; } return r; } 
inline void down(int &x, int y) { x = x - y < 0 ? x - y + Mod : x - y; } 

inline void NTT(vector<int> &a, int inv)
{
    int n = a.size(); vector<unsigned long long> f(n); 
    REP(i, 0, n - 1) f[i] = a[i];
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
		if ( (Mid == 1 << 8) || (Mid == 1 << 16) ) REP(i, 0, n - 1) f[i] %= Mod;
    }
    if ( inv == -1 ) 
    {
        inv = power(n, Mod - 2); 
        REP(i, 0, n - 1) f[i] = (f[i] % Mod) * inv;
    }
    REP(i, 0, n - 1) a[i] = f[i] % Mod;
}

inline vector<int> operator * (vector<int> a, vector<int> b)
{
    int n = a.size(), m = b.size(), len = 1; 
    if ( n + m <= 18 ) 
    {
        vector<long long> c(n + m - 1); vector<int> d(n + m - 1);
        REP(i, 0, n - 1) REP(j, 0, m - 1) c[i + j] += 1ll * a[i] * b[j];
        REP(i, 0, n + m - 2) d[i] = c[i] % Mod; return d;
    }
	int N = n + m - 1;
    while ( len < N ) len <<= 1; a.resize(len); b.resize(len);
    NTT(a, 1); NTT(b, 1); REP(i, 0, len - 1) a[i] = 1ll * a[i] * b[i] % Mod; NTT(a, -1);
	return a;
}

inline void Solve(int l, int r)
{
	if ( l == r ) { down(f[l + l], f[l]); return ; } 
	int Mid = l + r >> 1; Solve(l, Mid);
	vector<int> A(Mid - l + 1), B(r - Mid);
	REP(i, l, Mid) A[i - l] = 1ll * f[i] * b[i] % Mod;
	REP(i, Mid + 1, r) B[i - Mid - 1] = a[i];
	N = min(r - l, n / 2 - l - Mid + 1);
	if ( N <= 0 ) goto Next ;
	if (A.size() > N) A.resize(N);
	if (B.size() > N) B.resize(N);
	
	A = A * B;
	for ( int i = 0; i < A.size(); ++ i ) down(f[i + l + Mid + 1], A[i]);
Next : ;
	Solve(Mid + 1, r);
}

inline void read(int &x)
{
	x = 0; char c = getchar();
	while ( c < '0' || c > '9' ) c = getchar();
	while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); } 
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("musician.in", "r", stdin);
	freopen("musician.out", "w", stdout);
#endif
	read(n); REP(i, 1, n) read(a[i]);
	REP(i, 2, n) a[i] = 1ll * a[i - 1] * a[i] % Mod;
	REP(i, 1, n / 2) { f[i] = a[i]; b[i] = power(a[i], Mod - 2); } 
	Solve(1, n / 2);
	ans = a[n]; REP(i, 1, n / 2) ans = (ans - 1ll * f[i] * b[i] % Mod * a[n - i]) % Mod;
	printf("%d\n", (ans + Mod) % Mod);
	return 0;
}
