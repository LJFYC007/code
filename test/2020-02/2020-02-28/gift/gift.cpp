#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;

int r[maxn], fac[maxn], inv[maxn];

inline int mul(int a, int b, int Mod)
{
    a %= Mod, b %= Mod;
    return ((a * b - (long long)((long long)((long double)a / Mod * b + 1e-3) * Mod)) % Mod + Mod) % Mod;
}
inline int power(int a, int b, int Mod) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

namespace Math {
    inline int pw(int base, int p, const int mod) {
        static int res;
        for (res = 1; p; p >>= 1, base = static_cast<long long> (base) * base % mod) if (p & 1) res = static_cast<long long> (res) * base % mod;
        return res;
    }
    inline int inv(int x, const int mod) { return pw(x, mod - 2, mod); }
}

const int mod1 = 998244353, mod2 = 1004535809, mod3 = 469762049, G = 3;
const long long mod_1_2 = static_cast<long long> (mod1) * mod2;
const int inv_1 = Math::inv(mod1, mod2), inv_2 = Math::inv(mod_1_2 % mod3, mod3);
struct Int {
    int A, B, C;
    explicit inline Int() { }
    explicit inline Int(int __num) : A(__num), B(__num), C(__num) { }
    explicit inline Int(int __A, int __B, int __C) : A(__A), B(__B), C(__C) { }
    static inline Int reduce(const Int &x) {
        return Int(x.A + (x.A >> 31 & mod1), x.B + (x.B >> 31 & mod2), x.C + (x.C >> 31 & mod3));
    }
    inline friend Int operator + (const Int &lhs, const Int &rhs) {
        return reduce(Int(lhs.A + rhs.A - mod1, lhs.B + rhs.B - mod2, lhs.C + rhs.C - mod3));
    }
    inline friend Int operator - (const Int &lhs, const Int &rhs) {
        return reduce(Int(lhs.A - rhs.A, lhs.B - rhs.B, lhs.C - rhs.C));
    }
    inline friend Int operator * (const Int &lhs, const Int &rhs) {
        return Int(static_cast<long long> (lhs.A) * rhs.A % mod1, static_cast<long long> (lhs.B) * rhs.B % mod2, static_cast<long long> (lhs.C) * rhs.C % mod3);
    }
    inline int get() {
        long long x = static_cast<long long> (B - A + mod2) % mod2 * inv_1 % mod2 * mod1 + A;
        return (static_cast<long long> (C - x % mod3 + mod3) % mod3 * inv_2 % mod3 * (mod_1_2 % mod) % mod + x) % mod;
    }
} ;

namespace Poly {
#define N (maxn << 1)
    int lim, s, rev[N];
    Int Wn[N | 1];
    inline void init(int n) {
        s = -1, lim = 1; while (lim < n) lim <<= 1, ++s;
        for (register int i = 1; i < lim; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
        const Int t(Math::pw(G, (mod1 - 1) / lim, mod1), Math::pw(G, (mod2 - 1) / lim, mod2), Math::pw(G, (mod3 - 1) / lim, mod3));
        *Wn = Int(1); for (register Int *i = Wn; i != Wn + lim; ++i) *(i + 1) = *i * t;
    }
    inline void NTT(Int *A, const int op = 1) {
        for (register int i = 1; i < lim; ++i) if (i < rev[i]) std::swap(A[i], A[rev[i]]);
        for (register int mid = 1; mid < lim; mid <<= 1) {
            const int t = lim / mid >> 1;
            for (register int i = 0; i < lim; i += mid << 1) {
                for (register int j = 0; j < mid; ++j) {
                    const Int W = op ? Wn[t * j] : Wn[lim - t * j];
                    const Int X = A[i + j], Y = A[i + j + mid] * W;
                    A[i + j] = X + Y, A[i + j + mid] = X - Y;
                }
            }
        }
        if (!op) {
            const Int ilim(Math::inv(lim, mod1), Math::inv(lim, mod2), Math::inv(lim, mod3));
            for (register Int *i = A; i != A + lim; ++i) *i = (*i) * ilim;
        }
    }
#undef N
}

Int A[maxn], B[maxn];

inline void Mul(int *f, int *g, int *h, int n, int op)
{
	int len = 1;
    op = op == 1 ? n : (n << 1);
	while ( len < op ) len <<= 1;
	REP(i, n, len - 1) g[i] = h[i] = 0;
    REP(i, 0, len - 1) { A[i] = Int(g[i] % mod); B[i] = Int(h[i] % mod); }
    Poly::init(len);
    Poly::NTT(A); Poly::NTT(B);
    for (int i = 0; i < Poly::lim; ++i) A[i] = A[i] * B[i];
    Poly::NTT(A, 0);
    REP(i, 0, len - 1) f[i] = A[i].get();
    /*
    REP(i, 0, len - 1) { a[0][i] = a[1][i] = a[2][i] = g[i]; b[0][i] = b[1][i] = b[2][i] = h[i]; }
    int Mod[3] = {469762049, 998244353, 1004535809}, p = 1e9 + 7;;
    REP(i, 0, 2)
    {
        NTT(a[i], len, Mod[i], 1); NTT(b[i], len, Mod[i], 1);
        REP(j, 0, len - 1) a[i][j] = a[i][j] * b[i][j] % Mod[i];
        NTT(a[i], len, Mod[i], -1);
    }
	int M = Mod[0] * Mod[1];
    REP(i, 0, len - 1)
    {
        long long A = (mul(a[0][i] * Mod[1] % M, power(Mod[1] % Mod[0], Mod[0] - 2, Mod[0]), M) +
                       mul(a[1][i] * Mod[0] % M, power(Mod[0] % Mod[1], Mod[1] - 2, Mod[1]), M)) % M;
        long long k = ((a[2][i] - A) % Mod[2] + Mod[2]) % Mod[2] * power(M % Mod[2], Mod[2] - 2, Mod[2]) % Mod[2];
        f[i] = ((k % p) * (M % p) % p + A % p) % p;
    }*/
}

const int Mod = 1e9 + 7;

inline void Solve(int *f, int n)
{
	if ( n == 1 ) { f[0] = 0; f[1] = 1; return ; }
	if ( n & 1 )
	{
        int g[n * 4], h[n * 4];
		Solve(g, n - 1);
		REP(i, 2, n) h[i] = 0; h[0] = n - 1; h[1] = 1;
		Mul(f, g, h, n + 1, 0);
		return ;
	}
	int a[n * 4], b[n * 4], g[n * 4], h[n * 4];
	Solve(g, n / 2);
    int N = (n / 2) + 1, x = 1;
	REP(i, 0, N - 1)
	{
		a[i] = fac[N - i - 1] * g[N - i - 1] % Mod;
		b[i] = x * inv[i] % Mod;
		x = x * (n / 2) % Mod;
	}
	Mul(h, a, b, N, 0);
    REP(i, 0, N - 1) if ( i < N - i - 1 ) swap(h[i], h[N - i - 1]);
	REP(i, 0, N - 1) h[i] = h[i] * inv[i] % Mod;
    REP(i, N, n) g[i] = h[i] = 0;
	Mul(f, g, h, n + 1, 1);
}

int n, l, R, f[maxn];

signed main()
{
    //freopen("gift.in", "r", stdin);
    //freopen("gift.out", "w", stdout);
	scanf("%lld%lld%lld", &n, &l, &R);
    int a[maxn];
    REP(i, 1, n) scanf("%lld", &a[i]);
	fac[0] = inv[0] = 1; REP(i, 1, n + 10) fac[i] = fac[i - 1] * i % Mod;
	inv[n + 10] = power(fac[n + 10], Mod - 2, Mod); for ( int i = n + 9; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	if ( l > 1 ) Solve(f, l - 1); else f[0] = 1;
    int sum, ret = 0;
    REP(j, 1, l - 1) ret = (ret + a[j] * f[j] * ((l - 1 - j & 1) ? -1 : 1)) % Mod;
	REP(i, l, R)
	{
        f[i] = 0; for ( int j = i; j >= 1; -- j) f[j] = (f[j] * (i - 1) + f[j - 1]) % Mod;
        f[0] = 0;
		sum = 0;
		REP(j, 1, i) sum = (sum + a[j] * f[j] * ((i - j & 1) ? -1 : 1)) % Mod;
		printf("%lld ", (sum - ret + Mod + Mod) % Mod);
        ret = sum;
	}
	return 0;
}
